#pragma once

#include <string>
#include <json11.hpp>

class ValidatorImpl
{
public:
  typedef json11::Json Json;

  ValidatorImpl();

  ValidatorImpl(const Json &schema);

  bool validate(const Json &json);

  bool validate(const Json &json, const Json &schema);

  bool findRef(const std::string &uri, Json &schema);

  bool validate_$ref(const Json &, const Json &, const Json &);

  bool validate_additionalItems(const Json &, const Json &, const Json &);

  bool validate_additionalProperties(const Json &, const Json &, const Json &);

  bool validate_allOf(const Json &, const Json &, const Json &);

  bool validate_anyOf(const Json &, const Json &, const Json &);

  bool validate_dependencies(const Json &, const Json &, const Json &);

  bool validate_enum(const Json &, const Json &, const Json &);

  bool validate_format(const Json &, const Json &, const Json &) { return true; }

  bool validate_items(const Json &, const Json &, const Json &);

  bool validate_maxItems(const Json &, const Json &, const Json &);

  bool validate_maxLength(const Json &, const Json &, const Json &);

  bool validate_maxProperties(const Json &, const Json &, const Json &);

  bool validate_maximum(const Json &, const Json &, const Json &);

  bool validate_minItems(const Json &, const Json &, const Json &);

  bool validate_minLength(const Json &, const Json &, const Json &);

  bool validate_minProperties(const Json &, const Json &, const Json &);

  bool validate_minimum(const Json &, const Json &, const Json &);

  bool validate_multipleOf(const Json &, const Json &, const Json &);

  bool validate_not(const Json &, const Json &, const Json &);

  bool validate_oneOf(const Json &, const Json &, const Json &);

  bool validate_pattern(const Json &, const Json &, const Json &);

  bool validate_patternProperties(const Json &, const Json &, const Json &);

  bool validate_properties(const Json &, const Json &, const Json &);

  bool validate_required(const Json &, const Json &, const Json &);

  bool validate_type(const Json &, const Json &, const Json &);

  bool validate_uniqueItems(const Json &, const Json &, const Json &);

private:
  typedef bool (ValidatorImpl::*Function)(const Json &, const Json &, const Json &);

  const Json m_schema;
  const std::map<std::string, Function> m_validators;
};


