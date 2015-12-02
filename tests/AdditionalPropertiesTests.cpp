#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(AdditionalProperties, Object)
{
  ValidatorImpl v;
  const std::string json = R"({"p1": 1, "p2": 2, "p3": 3, "p4": 4, "p5": 5})";
  const std::string additionalProperties = R"({})";
  const std::string schema = R"({"additionalProperties": {}})";
  ASSERT_EQ(v.validate_additionalProperties(_json_(json), _json_(additionalProperties), _json_(schema)), true);
}

TEST(AdditionalProperties, Allowed)
{
  ValidatorImpl v;
  const std::string json = R"({"p1": 1, "p2": 2, "p3": 3, "p4": 4, "p5": 5})";
  const std::string additionalProperties = R"(true)";
  const std::string schema = R"({"additionalProperties": true})";
  ASSERT_EQ(v.validate_additionalProperties(_json_(json), _json_(additionalProperties), _json_(schema)), true);
}

TEST(AdditionalProperties, DisallowedNoPropertiesNoPatternProperties)
{
  ValidatorImpl v;
  const std::string json = R"({"p1": 1, "p2": 2, "p3": 3, "p4": 4, "p5": 5})";
  const std::string additionalProperties = R"(false)";
  const std::string schema = R"({"additionalProperties": false})";
  ASSERT_EQ(v.validate_additionalProperties(_json_(json), _json_(additionalProperties), _json_(schema)), false);
}

TEST(AdditionalProperties, DisallowedNoPropertiesSuccess)
{
  ValidatorImpl v;
  const std::string json = R"({"p1": 1, "p2": 2, "p3": 3, "p4": 4, "p5": 5})";
  const std::string additionalProperties = R"(false)";
  const std::string schema = R"(
{
  "additionalProperties": false,
  "patternProperties":
  {
    ".+": {}
  }
}
)";
  ASSERT_EQ(v.validate_additionalProperties(_json_(json), _json_(additionalProperties), _json_(schema)), true);
}

TEST(AdditionalProperties, DisallowedNoPropertiesFailure)
{
  ValidatorImpl v;
  const std::string json = R"({"1": 1, "2": 2, "3": 3, "p1": 1})";
  const std::string additionalProperties = R"(false)";
  const std::string schema = R"(
{
  "additionalProperties": false,
  "patternProperties":
  {
    ".": {}
  }
}
)";
  ASSERT_EQ(v.validate_additionalProperties(_json_(json), _json_(additionalProperties), _json_(schema)), false);
}

TEST(AdditionalProperties, DisallowedNoPatternPropertiesSuccess)
{
  ValidatorImpl v;
  const std::string json = R"({"p1": 1, "p2": 2, "p3": 3})";
  const std::string additionalProperties = R"(false)";
  const std::string schema = R"(
{
  "additionalProperties": false,
  "properties": {"p1": {}, "p2": {}, "p3": {}}
}
)";
  ASSERT_EQ(v.validate_additionalProperties(_json_(json), _json_(additionalProperties), _json_(schema)), true);
}

TEST(AdditionalProperties, DisallowedNoPatternPropertiesFailure)
{
  ValidatorImpl v;
  const std::string json = R"({"p1": 1, "p2": 2, "p3": 3, "p4": 4})";
  const std::string additionalProperties = R"(false)";
  const std::string schema = R"(
{
  "additionalProperties": false,
  "properties": {"p1": {}, "p2": {}, "p3": {}}
}
)";
  ASSERT_EQ(v.validate_additionalProperties(_json_(json), _json_(additionalProperties), _json_(schema)), false);
}

TEST(AdditionalProperties, DisallowedSuccess)
{
  ValidatorImpl v;
  const std::string json = R"({"1": 1, "2": 2, "3": 3, "p1": 1, "p2": 2, "p3": 3})";
  const std::string additionalProperties = R"(false)";
  const std::string schema = R"(
{
  "additionalProperties": false,
  "patternProperties": {".": {}},
  "properties": {"p1": {}, "p2": {}, "p3": {}}
}
)";
  ASSERT_EQ(v.validate_additionalProperties(_json_(json), _json_(additionalProperties), _json_(schema)), true);
}

TEST(AdditionalProperties, DisallowedFaiure)
{
  ValidatorImpl v;
  const std::string json = R"({"1": 1, "2": 2, "3": 3, "p1": 1, "p2": 2, "p3": 3, "p4": 4})";
  const std::string additionalProperties = R"(false)";
  const std::string schema = R"(
{
  "additionalProperties": false,
  "patternProperties": {".": {}},
  "properties": {"p1": {}, "p2": {}, "p3": {}}
}
)";
  ASSERT_EQ(v.validate_additionalProperties(_json_(json), _json_(additionalProperties), _json_(schema)), false);
}
