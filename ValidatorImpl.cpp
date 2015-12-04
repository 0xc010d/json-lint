#include <sstream>
#include <regex>
#include <cmath>
#include <assert.h>
#include "ValidatorImpl.h"

using namespace json11;

ValidatorImpl::ValidatorImpl() : ValidatorImpl(Json::object{}) { }

ValidatorImpl::ValidatorImpl(const Json &schema) : m_schema(schema) { }

bool ValidatorImpl::validate(const Json &json)
{
  return validate(json, m_schema);
}

bool ValidatorImpl::validate(const Json &json, const Json &schema)
{
  typedef bool (ValidatorImpl::*ValidatorFunction)(const json11::Json &, const json11::Json &, const json11::Json &);
  static const std::map<std::string, ValidatorFunction> validatorFunctions{
    {"$ref",                 &ValidatorImpl::validate_$ref},
    {"additionalItems",      &ValidatorImpl::validate_additionalItems},
    {"additionalProperties", &ValidatorImpl::validate_additionalProperties},
    {"allOf",                &ValidatorImpl::validate_allOf},
    {"anyOf",                &ValidatorImpl::validate_anyOf},
    {"dependencies",         &ValidatorImpl::validate_dependencies},
    {"enum",                 &ValidatorImpl::validate_enum},
    {"format",               &ValidatorImpl::validate_format},
    {"items",                &ValidatorImpl::validate_items},
    {"maxItems",             &ValidatorImpl::validate_maxItems},
    {"maxLength",            &ValidatorImpl::validate_maxLength},
    {"maxProperties",        &ValidatorImpl::validate_maxProperties},
    {"maximum",              &ValidatorImpl::validate_maximum},
    {"minItems",             &ValidatorImpl::validate_minItems},
    {"minLength",            &ValidatorImpl::validate_minLength},
    {"minProperties",        &ValidatorImpl::validate_minProperties},
    {"minimum",              &ValidatorImpl::validate_minimum},
    {"multipleOf",           &ValidatorImpl::validate_multipleOf},
    {"not",                  &ValidatorImpl::validate_not},
    {"oneOf",                &ValidatorImpl::validate_oneOf},
    {"pattern",              &ValidatorImpl::validate_pattern},
    {"patternProperties",    &ValidatorImpl::validate_patternProperties},
    {"properties",           &ValidatorImpl::validate_properties},
    {"required",             &ValidatorImpl::validate_required},
    {"type",                 &ValidatorImpl::validate_type},
    {"uniqueItems",          &ValidatorImpl::validate_uniqueItems},
  };

  bool result = true;
  assert(schema.is_object());
  for (auto &key : schema.object_items()) {
    if (validatorFunctions.find(key.first) != validatorFunctions.end()) {
      auto validatorFunction = std::bind(validatorFunctions.at(key.first), &*this, json, key.second, schema);
      result = result & validatorFunction();
    }
  }
  return result;
}

bool ValidatorImpl::findRef(const std::string &uri, Json &schema)
{
  if (uri.find("#") != 0) {
    return false;
  }

  std::string path = uri.substr(1, uri.length() - 1);
  if (path.empty()) {
    schema = m_schema;
    return true;
  }

  if (path.find("/") != 0) {
    return false;
  }

  if (path.rfind("/") == path.length() - 1) {
    return false;
  }

  const Json *current = &m_schema;

  std::stringstream stream;
  stream << path.substr(1, path.length() - 1);
  std::string component;

  while (std::getline(stream, component, '/')) {
    if (current->object_items().find(component) == current->object_items().end()) {
      return false;
    }
    auto &newCurrent = current->object_items().at(component);
    if (!newCurrent.is_object()) {
      return false;
    }
    current = &newCurrent;
  }

  schema = *current;

  return true;
}

bool ValidatorImpl::validate_$ref(const Json &json, const Json &ref, const Json &)
{
  Json schema;
  assert(ref.is_string());
  if (!findRef(ref.string_value(), schema))
    return false;
  return validate(json, schema);
}

bool ValidatorImpl::validate_additionalItems(const Json &json, const Json &additionalItems, const Json &schema)
{
  if (!json.is_array())
    return true;
  assert(schema.is_object());
  auto &schemaObject = schema.object_items();
  if (schemaObject.find("items") == schemaObject.end())
    return true;
  if (schemaObject.at("items").is_object())
    return true;
  if (additionalItems.is_object())
    return true;
  assert(additionalItems.is_bool());
  if (additionalItems.bool_value())
    return true;
  assert(schemaObject.at("items").is_array());
  return json.array_items().size() <= schemaObject.at("items").array_items().size();
}

bool ValidatorImpl::validate_additionalProperties(const Json &json, const Json &additionalProperties, const Json &schema)
{
  if (!json.is_object())
    return true;
  if (additionalProperties.is_object())
    return true;
  assert(additionalProperties.is_bool());
  if (additionalProperties.bool_value())
    return true;

  std::vector<std::string> keys;
  for (auto &key : json.object_items())
    keys.push_back(key.first);
  assert(schema.is_object());
  auto &schemaObject = schema.object_items();
  if (schemaObject.find("properties") != schemaObject.end()) {
    assert(schemaObject.at("properties").is_object());
    auto &properties = schemaObject.at("properties").object_items();
    for (auto &property : properties)
      keys.erase(
        std::remove(keys.begin(), keys.end(), property.first),
        keys.end()
      );
  }
  if (schemaObject.find("patternProperties") != schemaObject.end()) {
    assert(schemaObject.at("patternProperties").is_object());
    auto &patternProperties = schemaObject.at("patternProperties").object_items();
    for (auto &patternProperty : patternProperties) {
      std::regex regex(patternProperty.first);
      std::smatch match;
      auto check = [&](const std::string &key) { return std::regex_match(key, match, regex); };
      keys.erase(
        std::remove_if(keys.begin(), keys.end(), check),
        keys.end()
      );
    }
  }

  return keys.size() == 0;
}

bool ValidatorImpl::validate_allOf(const Json &json, const Json &allOf, const Json &)
{
  bool result = true;
  assert(allOf.is_array());
  assert(!allOf.array_items().empty());
  for (auto &one : allOf.array_items()) {
    result = result && validate(json, one);
  }
  return result;
}

bool ValidatorImpl::validate_anyOf(const Json &json, const Json &anyOf, const Json &)
{
  assert(anyOf.is_array());
  assert(!anyOf.array_items().empty());
  for (auto &one : anyOf.array_items()) {
    if (validate(json, one))
      return true;
  }
  return false;
}

bool ValidatorImpl::validate_dependencies(const Json &json, const Json &dependencies, const Json &)
{
  if (!json.is_object())
    return true;
  bool result = true;
  auto &object = json.object_items();
  assert(dependencies.is_object());
  for (auto &dependency : dependencies.object_items()) {
    if (object.find(dependency.first) == object.end())
      continue;
    if (dependency.second.is_object()) {
      result = result && validate(json, dependency.second);
    }
    else {
      assert(dependency.second.is_array());
      assert(!dependency.second.array_items().empty());
      for (auto &key : dependency.second.array_items()) {
        assert(key.is_string());
        result = result && object.find(key.string_value()) != object.end();
      }
    }
  }
  return result;
}

bool ValidatorImpl::validate_enum(const Json &json, const Json &_enum, const Json &)
{
  assert(_enum.is_array());
  assert(!_enum.array_items().empty());
  for (auto &item : _enum.array_items()) {
    if (json == item)
      return true;
  }
  return false;
}

bool ValidatorImpl::validate_items(const Json &json, const Json &items, const Json &)
{
  if (!json.is_array())
    return true;
  bool result = true;
  auto &array = json.array_items();
  if (items.is_object()) {
    for (auto &value : array) {
      result = result && validate(value, items);
    }
  }
  else {
    assert(items.is_array());
    auto &itemsArray = items.array_items();
    if (itemsArray.size() < array.size()) {
      return false;
    }
    for (auto it = itemsArray.begin(); it < itemsArray.end(); ++it) {
      auto index = std::distance(itemsArray.begin(), it);
      result = result && validate(array[index], *it);
    }
  }
  return result;
}

bool ValidatorImpl::validate_maxItems(const Json &json, const Json &maxItems, const Json &)
{
  if (!json.is_array())
    return true;
  assert(maxItems.is_number());
  return json.array_items().size() <= (size_t)maxItems.int_value();
}

bool ValidatorImpl::validate_maxLength(const Json &json, const Json &maxLength, const Json &)
{
  if (!json.is_string())
    return true;
  assert(maxLength.is_number());
  return json.string_value().length() <= (size_t)maxLength.int_value();
}

bool ValidatorImpl::validate_maxProperties(const Json &json, const Json &maxProperties, const Json &)
{
  if (!json.is_object())
    return true;
  assert(maxProperties.is_number());
  return json.object_items().size() <= (size_t)maxProperties.int_value();
}

bool ValidatorImpl::validate_maximum(const Json &json, const Json &maximum, const Json &schema)
{
  if (!json.is_number())
    return true;
  assert(schema.is_object());
  auto &schemaObject = schema.object_items();
  assert(json.is_number());
  if (schemaObject.find("exclusiveMaximum") == schemaObject.end() || !schemaObject.at("exclusiveMaximum").bool_value())
    return json <= maximum;
  return json < maximum;
}

bool ValidatorImpl::validate_minItems(const Json &json, const Json &minItems, const Json &)
{
  if (!json.is_array())
    return true;
  assert(minItems.is_number());
  return json.array_items().size() >= (size_t)minItems.int_value();
}

bool ValidatorImpl::validate_minLength(const Json &json, const Json &minLength, const Json &)
{
  if (!json.is_string())
    return true;
  assert(minLength.is_number());
  return json.string_value().length() >= (size_t)minLength.int_value();
}

bool ValidatorImpl::validate_minProperties(const Json &json, const Json &minProperties, const Json &)
{
  if (!json.is_object())
    return true;
  assert(minProperties.is_number());
  return json.object_items().size() >= (size_t)minProperties.int_value();
}

bool ValidatorImpl::validate_minimum(const Json &json, const Json &minimum, const Json &schema)
{
  if (!json.is_number())
    return true;
  assert(schema.is_object());
  auto &schemaObject = schema.object_items();
  assert(json.is_number());
  if (schemaObject.find("exclusiveMinimum") == schemaObject.end() || !schemaObject.at("exclusiveMinimum").bool_value())
    return json >= minimum;
  return json > minimum;
}

bool ValidatorImpl::validate_multipleOf(const Json &json, const Json &multipleOf, const Json &)
{
  if (!json.is_number())
    return true;
  double integerPart;
  assert(multipleOf.is_number());
  return std::modf(json.number_value() / multipleOf.number_value(), &integerPart) == 0;
}

bool ValidatorImpl::validate_not(const Json &json, const Json &_not, const Json &)
{
  return !validate(json, _not);
}

bool ValidatorImpl::validate_oneOf(const Json &json, const Json &oneOf, const Json &)
{
  int count = 0;
  assert(oneOf.is_array());
  for (auto &one : oneOf.array_items()) {
    if (validate(json, one))
      count++;
  }
  return count == 1;
}

bool ValidatorImpl::validate_pattern(const Json &json, const Json &pattern, const Json &)
{
  if (!json.is_string())
    return true;
  assert(pattern.is_string());
  std::regex regex(pattern.string_value());
  std::smatch match;
  return std::regex_match(json.string_value(), match, regex);
}

bool ValidatorImpl::validate_patternProperties(const Json &json, const Json &patternProperties, const Json &)
{
  if (!json.is_object())
    return true;
  bool result = true;
  auto &object = json.object_items();
  assert(patternProperties.is_object());
  for (auto &pattern : patternProperties.object_items()) {
    std::regex regex(pattern.first);
    std::smatch match;
    auto check = [&](const std::pair<std::string, Json> &value) { return std::regex_match(value.first, match, regex); };

    auto iterator = std::find_if(object.begin(), object.end(), check);
    while (iterator != object.end()) {
      result = result && validate(iterator->second, pattern.second);
      iterator = std::find_if(++iterator, object.end(), check);
    }
  }
  return result;
}

bool ValidatorImpl::validate_properties(const Json &json, const Json &properties, const Json &)
{
  if (!json.is_object())
    return true;
  bool result = true;
  auto &object = json.object_items();
  assert(properties.is_object());
  for (auto &property : properties.object_items()) {
    if (object.find(property.first) == object.end())
      continue;
    auto &value = object.at(property.first);
    result = result && validate(value, property.second);
  }
  return result;
}

bool ValidatorImpl::validate_required(const Json &json, const Json &required, const Json &)
{
  if (!json.is_object())
    return true;
  bool result = true;
  auto &object = json.object_items();
  assert(required.is_array());
  for (auto &key : required.array_items()) {
    assert(key.is_string());
    result = result && (object.find(key.string_value()) != object.end());
  }
  return result;
}

bool ValidatorImpl::validate_type(const Json &json, const Json &type, const Json &schema)
{
  if (type.is_array()) {
    assert(!type.array_items().empty());
    for (auto &t : type.array_items()) {
      if (validate_type(json, t, schema))
        return true;
    }
    return false;
  }
  assert(type.is_string());
  auto &typeString = type.string_value();
  if (typeString == "integer") {
    //there should be is_int method in Json. or Json::Type::INTEGER should be defined
    double integerPart;
    return json.is_number() && std::modf(json.number_value(), &integerPart) == 0;
  }
  typedef bool (Json::*TypeChecker)() const;
  static const std::map<std::string, TypeChecker> checkers{
    {"number",  &Json::is_number},
    {"string",  &Json::is_string},
    {"null",    &Json::is_null},
    {"boolean", &Json::is_bool},
    {"array",   &Json::is_array},
    {"object",  &Json::is_object},
  };
  assert(checkers.find(typeString) != checkers.end());
  auto checker = std::bind(checkers.at(typeString), &json);
  return checker();
}

bool ValidatorImpl::validate_uniqueItems(const Json &json, const Json &uniqueItems, const Json &)
{
  if (!json.is_array())
    return true;
  assert(uniqueItems.is_bool());
  if (!uniqueItems.bool_value())
    return true;
  std::vector<Json> values;
  for (auto &item : json.array_items()) {
    if (std::find(values.begin(), values.end(), item) != values.end())
      return false;
    values.push_back(item);
  }
  return true;
}
