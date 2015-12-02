#pragma once

#include <json11.hpp>
#include <memory>

class ValidatorImpl;

class Validator
{
public:
  Validator(const json11::Json &schema);

  ~Validator();

  bool validate(const json11::Json &json);

private:
  ValidatorImpl *m_impl;
};
