#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(AdditionalProperties, Object)
{
  ValidatorImpl v;
  const std::string json = R"({"p1": 1, "p2": 2, "p3": 3, "p4": 4, "p5": 5})";
  const std::string additionalProperties = R"({})";
  const std::string schema = R"({"additionalProperties": {}})";
  ASSERT_EQ(v.validate_additionalItems(_json_(json), _json_(additionalProperties), _json_(schema)), true);
}

TEST(AdditionalProperties, Allowed)
{
  ValidatorImpl v;
  const std::string json = R"({"p1": 1, "p2": 2, "p3": 3, "p4": 4, "p5": 5})";
  const std::string additionalProperties = R"(true)";
  const std::string schema = R"({"additionalProperties": true})";
  ASSERT_EQ(v.validate_additionalItems(_json_(json), _json_(additionalProperties), _json_(schema)), true);
}
