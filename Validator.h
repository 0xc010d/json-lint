#pragma once

#include <json11.hpp>
#include <memory>

class ValidatorImpl;

class Validator
{
public:
  Validator(const json11::Json &schema);

  bool validate(const json11::Json &json);

private:
  std::unique_ptr<ValidatorImpl> m_impl;
};
