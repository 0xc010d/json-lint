#pragma once

#include <string>
#include <json11.hpp>

class ValidatorImpl
{
public:
  ValidatorImpl();

  ValidatorImpl(const json11::Json &schema);

  bool validate(const json11::Json &json);

  bool validate(const json11::Json &json, const json11::Json &schema);

  bool findRef(const std::string &uri, json11::Json &schema);

  bool validate_$ref(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_additionalItems(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_additionalProperties(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_allOf(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_anyOf(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_dependencies(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_enum(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_format(const json11::Json &, const json11::Json &, const json11::Json &) { return true; }

  bool validate_items(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_maxItems(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_maxLength(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_maxProperties(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_maximum(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_minItems(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_minLength(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_minProperties(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_minimum(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_multipleOf(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_not(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_oneOf(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_pattern(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_patternProperties(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_properties(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_required(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_type(const json11::Json &, const json11::Json &, const json11::Json &);

  bool validate_uniqueItems(const json11::Json &, const json11::Json &, const json11::Json &);

private:
  const json11::Json m_schema;
};
