#pragma once

#import <json11.hpp>
#import <assert.h>

inline
__attribute__((always_inline))
json11::Json _json_(const std::string &string) {
  std::string error;
  auto json = json11::Json::parse(string, error);
  assert(error.empty());
  return json;
}
