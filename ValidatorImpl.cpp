#include <sstream>
#include <regex>
#include <cmath>
#include "ValidatorImpl.h"

ValidatorImpl::ValidatorImpl() : ValidatorImpl("{}") { }

ValidatorImpl::ValidatorImpl(const Schema &schema) : m_validators{
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
}, m_schema(schema) { }

ValidatorImpl::ValidatorImpl(const Json &schema) : ValidatorImpl(schema.object_items()) { }

bool ValidatorImpl::validate(const Json &json)
{
  return validate(json, m_schema);
}

bool ValidatorImpl::validate(const Json &json, const Schema &schema)
{
  bool result = true;
  for (auto &key : schema) {
    if (m_validators.find(key.first) != m_validators.end()) {
      auto &method = m_validators.at(key.first);
      result = result & (this->*method)(json, key.second, schema);
    }
  }
  return result;
}

bool ValidatorImpl::findRef(const std::string &uri, Schema &schema)
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

  const Schema *current = &m_schema;

  std::stringstream stream;
  stream << path.substr(1, path.length() - 1);
  std::string component;

  while (std::getline(stream, component, '/')) {
    if (component.empty()) {
      return false;
    }
    if (current->find(component) == current->end()) {
      return false;
    }
    auto &newCurrent = current->at(component);
    if (!newCurrent.is_object()) {
      return false;
    }
    current = &newCurrent.object_items();
  }

  schema = *current;

  return true;
}

bool ValidatorImpl::validate_$ref(const Json &json, const Json &ref, const Schema &)
{
  Schema refSchema;
  if (!findRef(ref.string_value(), refSchema))
    return false;
  return validate(json, refSchema);
}

bool ValidatorImpl::validate_additionalItems(const Json &json, const Json &additionalItems, const Schema &schema)
{
  if (schema.find("items") == schema.end())
    return true;
  if (schema.at("items").is_object())
    return true;
  if (additionalItems.is_object() || additionalItems.bool_value())
    return true;
  return json.array_items().size() <= schema.at("items").array_items().size();
}

bool ValidatorImpl::validate_additionalProperties(const Json &json, const Json &additionalProperties, const Schema &schema)
{
  if (additionalProperties.is_object())
    return true;
  if (additionalProperties.bool_value())
    return true;

  std::vector<std::string> keys;
  for (auto &key : json.object_items())
    keys.push_back(key.first);
  if (schema.find("properties") != schema.end()) {
    auto &properties = schema.at("properties").object_items();
    for (auto &property : properties)
      keys.erase(
        std::remove(keys.begin(), keys.end(), property.first),
        keys.end()
      );
  }
  if (schema.find("patternProperties") != schema.end()) {
    auto &patternProperties = schema.at("patternProperties").object_items();
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

bool ValidatorImpl::validate_allOf(const Json &json, const Json &allOf, const Schema &)
{
  bool result = true;
  for (auto &one : allOf.array_items()) {
    result = result && validate(json, one.object_items());
  }
  return result;
}

bool ValidatorImpl::validate_anyOf(const Json &json, const Json &anyOf, const Schema &)
{
  for (auto &one : anyOf.array_items()) {
    if (validate(json, one.object_items()))
      return true;
  }
  return false;
}

bool ValidatorImpl::validate_dependencies(const Json &json, const Json &dependencies, const Schema &)
{
  bool result = true;
  auto &object = json.object_items();
  for (auto &dependency : dependencies.object_items()) {
    if (object.find(dependency.first) == object.end())
      continue;
    if (dependency.second.is_object()) {
      result = result && validate(json, dependency.second.object_items());
    }
    else {
      for (auto &key : dependency.second.array_items()) {
        result = result && object.find(key.string_value()) != object.end();
      }
    }
  }
  return result;
}

bool ValidatorImpl::validate_enum(const Json &json, const Json &_enum, const Schema &)
{
  for (auto &item : _enum.array_items()) {
    if (json == item)
      return true;
  }
  return false;
}

bool ValidatorImpl::validate_items(const Json &json, const Json &items, const Schema &)
{
  bool result = true;
  auto &array = json.array_items();
  if (items.is_object()) {
    for (auto &value : array) {
      result = result && validate(value, items.object_items());
    }
  }
  else {
    if (items.array_items().size() < array.size()) {
      return false;
    }
    for (auto it = items.array_items().begin(); it < items.array_items().end(); ++it) {
      auto index = std::distance(items.array_items().begin(), it);
      result = result && validate(array[index], (*it).object_items());
    }
  }
  return result;
}

bool ValidatorImpl::validate_maxItems(const Json &json, const Json &maxItems, const Schema &)
{
  return json.array_items().size() <= maxItems.int_value();
}

bool ValidatorImpl::validate_maxLength(const Json &json, const Json &maxLength, const Schema &)
{
  return json.string_value().length() <= maxLength.int_value();
}

bool ValidatorImpl::validate_maxProperties(const Json &json, const Json &maxProperties, const Schema &)
{
  return json.object_items().size() <= maxProperties.int_value();
}

bool ValidatorImpl::validate_maximum(const Json &json, const Json &maximum, const Schema &schema)
{
  if (schema.find("exclusiveMaximum") == schema.end() || !schema.at("exclusiveMaximum").bool_value())
    return json <= maximum;
  return json < maximum;
}

bool ValidatorImpl::validate_minItems(const Json &json, const Json &minItems, const Schema &)
{
  return json.array_items().size() >= minItems.int_value();
}

bool ValidatorImpl::validate_minLength(const Json &json, const Json &minLength, const Schema &)
{
  return json.string_value().length() >= minLength.int_value();
}

bool ValidatorImpl::validate_minProperties(const Json &json, const Json &minProperties, const Schema &)
{
  return json.object_items().size() >= minProperties.int_value();
}

bool ValidatorImpl::validate_minimum(const Json &json, const Json &minimum, const Schema &schema)
{
  if (schema.find("exclusiveMinimum") == schema.end() || !schema.at("exclusiveMinimum").bool_value())
    return json >= minimum;
  return json > minimum;
}

bool ValidatorImpl::validate_multipleOf(const Json &json, const Json &multipleOf, const Schema &)
{
  double integerPart;
  return std::modf(json.number_value() / multipleOf.number_value(), &integerPart) == 0;
}

bool ValidatorImpl::validate_not(const Json &json, const Json &_not, const Schema &)
{
  return !validate(json, _not.object_items());
}

bool ValidatorImpl::validate_oneOf(const Json &json, const Json &oneOf, const Schema &)
{
  int count = 0;
  for (auto &one : oneOf.array_items()) {
    if (validate(json, one.object_items()))
      count++;
  }
  return count == 1;
}

bool ValidatorImpl::validate_pattern(const Json &json, const Json &pattern, const Schema &)
{
  std::regex regex(pattern.string_value());
  std::smatch match;
  return std::regex_match(json.string_value(), match, regex);
}

bool ValidatorImpl::validate_patternProperties(const Json &json, const Json &patternProperties, const Schema &)
{
  bool result = true;
  auto &object = json.object_items();
  for (auto &pattern : patternProperties.object_items()) {
    std::regex regex(pattern.first);
    std::smatch match;
    auto check = [&](const std::pair<std::string, Json> &value) { return std::regex_match(value.first, match, regex); };

    auto iterator = std::find_if(object.begin(), object.end(), check);
    while (iterator != object.end()) {
      result = result && validate(iterator->second, pattern.second.object_items());
      iterator = std::find_if(++iterator, object.end(), check);
    }
  }
  return result;
}

bool ValidatorImpl::validate_properties(const Json &json, const Json &properties, const Schema &)
{
  bool result = true;
  auto &object = json.object_items();
  for (auto &property : properties.object_items()) {
    if (object.find(property.first) == object.end())
      continue;
    auto &value = object.at(property.first);
    result = result && validate(value, property.second.object_items());
  }
  return result;
}

bool ValidatorImpl::validate_required(const Json &json, const Json &required, const Schema &)
{
  bool result = true;
  auto &object = json.object_items();
  for (auto &key : required.array_items()) {
    result = result && (object.find(key.string_value()) != object.end());
  }
  return result;
}

bool ValidatorImpl::validate_type(const Json &json, const Json &type, const Schema &schema)
{
  if (type.is_array()) {
    for (auto &t : type.array_items()) {
      if (validate_type(json, t, schema))
        return true;
    }
    return false;
  }
  if (type.string_value() == "integer") {
    //there should be is_int method in Json. or Json::Type::INTEGER should be defined
    double integerPart;
    return json.is_number() && std::modf(json.number_value(), &integerPart) == 0;
  }
  typedef bool (Json::*TypeChecker)() const;
  static const std::map<std::string, TypeChecker> checkers{
    {"number", &Json::is_number},
    {"string", &Json::is_string},
    {"null",   &Json::is_null},
    {"array",  &Json::is_array},
    {"object", &Json::is_object},
  };
  auto &checker = checkers.at(type.string_value());
  return (json.*checker)();
}

bool ValidatorImpl::validate_uniqueItems(const Json &json, const Json &uniqueItems, const Schema &)
{
  std::vector<Json> values;
  for (auto &item : json.array_items()) {
    if (std::find(values.begin(), values.end(), item) != values.end())
      return false;
    values.push_back(item);
  }
  return true;
}
