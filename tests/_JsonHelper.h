#pragma once

#import <json11.hpp>

inline
__attribute__((always_inline))
json11::Json _json_(const std::string &string) {
  std::string error;
  return json11::Json::parse(string, error);
}
