#pragma once

#include <json11.hpp>
#include <map>
#include <string>
#include <vector>

using namespace json11;

class Validator
{
public:
  typedef Json::object Schema;

  Validator(const Json &schema) : Validator(schema.object_items()) { }

  Validator(const Schema &schema);

  bool validate(const Json &json);

private:
  typedef bool (Validator::*Function)(const Json &, const Json &, const Schema &);

  const Schema m_schema;
  const std::map<std::string, Function> m_validators;
  std::vector<std::string> m_keys;

  bool validate(const Json &json, const Schema &schema);

  bool findRef(const std::string &uri, Schema &schema);

  bool validate_$ref(const Json &, const Json &, const Schema &);

  bool validate_additionalItems(const Json &, const Json &, const Schema &);

  bool validate_additionalProperties(const Json &, const Json &, const Schema &);

  bool validate_allOf(const Json &, const Json &, const Schema &);

  bool validate_anyOf(const Json &, const Json &, const Schema &);

  bool validate_dependencies(const Json &, const Json &, const Schema &);

  bool validate_enum(const Json &, const Json &, const Schema &);

  bool validate_format(const Json &, const Json &, const Schema &) { return true; }

  bool validate_items(const Json &, const Json &, const Schema &);

  bool validate_maxItems(const Json &, const Json &, const Schema &);

  bool validate_maxLength(const Json &, const Json &, const Schema &);

  bool validate_maxProperties(const Json &, const Json &, const Schema &);

  bool validate_maximum(const Json &, const Json &, const Schema &);

  bool validate_minItems(const Json &, const Json &, const Schema &);

  bool validate_minLength(const Json &, const Json &, const Schema &);

  bool validate_minProperties(const Json &, const Json &, const Schema &);

  bool validate_minimum(const Json &, const Json &, const Schema &);

  bool validate_multipleOf(const Json &, const Json &, const Schema &);

  bool validate_not(const Json &, const Json &, const Schema &);

  bool validate_oneOf(const Json &, const Json &, const Schema &);

  bool validate_pattern(const Json &, const Json &, const Schema &);

  bool validate_patternProperties(const Json &, const Json &, const Schema &);

  bool validate_properties(const Json &, const Json &, const Schema &);

  bool validate_required(const Json &, const Json &, const Schema &);

  bool validate_type(const Json &, const Json &, const Schema &);

  bool validate_uniqueItems(const Json &, const Json &, const Schema &);
};
