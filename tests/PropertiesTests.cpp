#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(Properties, NonObject)
{
  ValidatorImpl v;
  const std::string json = R"([])";
  const std::string properties = R"({"key": {"enum": [null]}})";
  const std::string schema = R"({"properties": {"key": {"enum": [null]}}})";
  ASSERT_EQ(v.validate_properties(_json_(json), _json_(properties), _json_(schema)), true);
}

TEST(Properties, EmptyObject)
{
  ValidatorImpl v;
  const std::string json = R"({})";
  const std::string properties = R"({"key": {"enum": [null]}})";
  const std::string schema = R"({"properties": {"key": {"enum": [null]}}})";
  ASSERT_EQ(v.validate_properties(_json_(json), _json_(properties), _json_(schema)), true);
}

TEST(Properties, PartialObject)
{
  ValidatorImpl v;
  const std::string json = R"({"key": "value", "1234": null})";
  const std::string properties = R"({"key": {"enum": ["value"]}})";
  const std::string schema = R"({"properties": {"key": {"enum": ["value"]}}})";
  ASSERT_EQ(v.validate_properties(_json_(json), _json_(properties), _json_(schema)), true);
}

TEST(Properties, Success)
{
  ValidatorImpl v;
  const std::string json = R"({"key1": "value1", "key2": null})";
  const std::string properties = R"({"key1": {"enum": ["value1"]}, "key2": {"enum": [null]}})";
  const std::string schema = R"({"key1": {"enum": ["value1"]}, "key2": {"enum": [null]}})";
  ASSERT_EQ(v.validate_properties(_json_(json), _json_(properties), _json_(schema)), true);
}

TEST(Properties, Failure)
{
  ValidatorImpl v;
  const std::string json = R"({"key1": "value", "key2": null})";
  const std::string properties = R"({"key1": {}, "key2": {"type": "number"}})";
  const std::string schema = R"({"properties": {"key1": {}, "key2": {"type": "number"}}})";
  ASSERT_EQ(v.validate_properties(_json_(json), _json_(properties), _json_(schema)), false);
}
