#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(PatternProperties, NonObject)
{
  ValidatorImpl v;
  const std::string json = R"([])";
  const std::string patternProperties = R"({".+": {"enum": [null]}})";
  const std::string schema = R"({"patternProperties": {".+": {"enum": [null]}}})";
  ASSERT_EQ(v.validate_patternProperties(_json_(json), _json_(patternProperties), _json_(schema)), true);
}

TEST(PatternProperties, EmptyObject)
{
  ValidatorImpl v;
  const std::string json = R"({})";
  const std::string patternProperties = R"({".+": {"enum": [null]}})";
  const std::string schema = R"({"patternProperties": {".+": {"enum": [null]}}})";
  ASSERT_EQ(v.validate_patternProperties(_json_(json), _json_(patternProperties), _json_(schema)), true);
}

TEST(PatternProperties, PartialObject)
{
  ValidatorImpl v;
  const std::string json = R"({"asdf": "string", "1234": null})";
  const std::string patternProperties = R"({"[\\D]+": {"enum": ["string"]}})";
  const std::string schema = R"({"patternProperties": {"[\\D]+": {"enum": ["string"]}}})";
  ASSERT_EQ(v.validate_patternProperties(_json_(json), _json_(patternProperties), _json_(schema)), true);
}

TEST(PatternProperties, Success)
{
  ValidatorImpl v;
  const std::string json = R"({"asdf": "string", "1234": null})";
  const std::string patternProperties = R"({"[\\D]+": {"enum": ["string"]}, "[\\d+]": {"enum": [null]}})";
  const std::string schema = R"({"[\\D]+": {"enum": ["string"]}, "[\\d+]": {"enum": [null]}})";
  ASSERT_EQ(v.validate_patternProperties(_json_(json), _json_(patternProperties), _json_(schema)), true);
}

TEST(PatternProperties, Failure)
{
  ValidatorImpl v;
  const std::string json = R"({"asdf": "string", "1234": null})";
  const std::string patternProperties = R"({"[\\d]+": {}, "[\\D]+": {"type": "number"}})";
  const std::string schema = R"({"patternProperties": {"[\\d]+": {}, "[\\D]+": {"type": "number"}}})";
  ASSERT_EQ(v.validate_patternProperties(_json_(json), _json_(patternProperties), _json_(schema)), false);
}
