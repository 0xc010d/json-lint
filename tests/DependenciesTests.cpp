#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(Dependencies, NonObject)
{
  ValidatorImpl v;
  const std::string json = R"([])";
  const std::string dependencies = R"({})";
  const std::string schema = R"({"dependencies": {}})";
  ASSERT_EQ(v.validate_dependencies(_json_(json), _json_(dependencies), _json_(schema)), true);
}

TEST(Dependencies, Empty)
{
  ValidatorImpl v;
  const std::string json = R"({})";
  const std::string dependencies = R"({})";
  const std::string schema = R"({"dependencies": {}})";
  ASSERT_EQ(v.validate_dependencies(_json_(json), _json_(dependencies), _json_(schema)), true);
}

TEST(Dependencies, EmptyObject)
{
  ValidatorImpl v;
  const std::string json = R"({})";
  const std::string dependencies = R"({"key1": {}, "key2": ["key1"]})";
  const std::string schema = R"({"dependencies": {"key1": {}, "key2": ["key1"]}})";
  ASSERT_EQ(v.validate_dependencies(_json_(json), _json_(dependencies), _json_(schema)), true);
}

TEST(Dependencies, SuccessObject)
{
  ValidatorImpl v;
  const std::string json = R"({"key1": "value", "key2": false})";
  const std::string dependencies = R"({"key1": {"properties": {"key2": {"type": "boolean"}}}})";
  const std::string schema = R"({"dependencies": {"key1": {"properties": {"key2": {"type": "boolean"}}}}})";
  ASSERT_EQ(v.validate_dependencies(_json_(json), _json_(dependencies), _json_(schema)), true);
}

TEST(Dependencies, FailureObject)
{
  ValidatorImpl v;
  const std::string json = R"({"key1": "value", "key2": 10})";
  const std::string dependencies = R"({"key1": {"properties": {"key2": {"type": "boolean"}}}})";
  const std::string schema = R"({"dependencies": {"key1": {"properties": {"key2": {"type": "boolean"}}}}})";
  ASSERT_EQ(v.validate_dependencies(_json_(json), _json_(dependencies), _json_(schema)), false);
}

TEST(Dependencies, SuccessArray)
{
  ValidatorImpl v;
  const std::string json = R"({"key1": "value", "key2": 10})";
  const std::string dependencies = R"({"key1": ["key2"]})";
  const std::string schema = R"({"dependencies": {"key1": ["key2"]}})";
  ASSERT_EQ(v.validate_dependencies(_json_(json), _json_(dependencies), _json_(schema)), true);
}

TEST(Dependencies, FailureArray)
{
  ValidatorImpl v;
  const std::string json = R"({"key1": "value", "key2": 10})";
  const std::string dependencies = R"({"key1": ["key2", "key3"]})";
  const std::string schema = R"({"dependencies": {"key1": ["key2", "key3"]}})";
  ASSERT_EQ(v.validate_dependencies(_json_(json), _json_(dependencies), _json_(schema)), false);
}

TEST(Dependencies, SuccessMix)
{
  ValidatorImpl v;
  const std::string json = R"({"key1": "value", "key2": false, "key3": "string"})";
  const std::string dependencies = R"(
{
  "key1": {
    "properties": {
      "key2": {"type": "boolean"}
    }
  },
  "key2": ["key3"]
}
)";
  const std::string schema = R"(
{
  "dependencies": {
    "key1": {
      "properties": {
        "key2": {"type": "boolean"}
      }
    },
    "key2": ["key3"]
  }
})";
  ASSERT_EQ(v.validate_dependencies(_json_(json), _json_(dependencies), _json_(schema)), true);
}

TEST(Dependencies, FailureMix)
{
  ValidatorImpl v;
  const std::string json1 = R"({"key1": "value", "key2": false, "key3": "string"})";
  const std::string json2 = R"({"key1": "value", "key2": 14, "key4": "string"})";
  const std::string dependencies = R"(
{
  "key1": {
    "properties": {
      "key2": {"type": "boolean"}
    }
  },
  "key2": ["key4"]
}
)";
  const std::string schema = R"(
{
  "dependencies": {
    "key1": {
      "properties": {
        "key2": {"type": "boolean"}
      }
    },
    "key2": ["key4"]
  }
})";
  ASSERT_EQ(v.validate_dependencies(_json_(json1), _json_(dependencies), _json_(schema)), false);
  ASSERT_EQ(v.validate_dependencies(_json_(json2), _json_(dependencies), _json_(schema)), false);
}
