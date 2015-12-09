#include "Validator.h"
#include "ValidatorImpl.h"

Validator::Validator(const json11::Json &schema) : m_impl(new ValidatorImpl(schema)) { }

bool Validator::validate(const json11::Json &json)
{
  return m_impl->validate(json);
}
