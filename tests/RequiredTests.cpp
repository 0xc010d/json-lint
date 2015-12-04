#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(Required, NonObject)
{
  ValidatorImpl v;
  const std::string json = R"([])";
  const std::string required = R"(["key1", "key2"])";
  const std::string schema = R"({"required": ["key1", "key2"]})";
  ASSERT_EQ(v.validate_required(_json_(json), _json_(required), _json_(schema)), true);
}

TEST(Required, Empty)
{
  ValidatorImpl v;
  const std::string json = R"({"key": "value"})";
  const std::string required = R"([])";
  const std::string schema = R"({"required": []})";
  ASSERT_EQ(v.validate_required(_json_(json), _json_(required), _json_(schema)), true);
}

TEST(Required, Exact)
{
  ValidatorImpl v;
  const std::string json = R"({"key1": "value1", "key2": false})";
  const std::string required = R"(["key1", "key2"])";
  const std::string schema = R"({"required": ["key1", "key2"]})";
  ASSERT_EQ(v.validate_required(_json_(json), _json_(required), _json_(schema)), true);
}

TEST(Required, Partial)
{
  ValidatorImpl v;
  const std::string json = R"({"key1": "value1", "key2": false})";
  const std::string required = R"(["key1"])";
  const std::string schema = R"({"required": ["key1"]})";
  ASSERT_EQ(v.validate_required(_json_(json), _json_(required), _json_(schema)), true);
}

TEST(Required, Failure)
{
  ValidatorImpl v;
  const std::string json = R"({"key1": "value1", "key2": false})";
  const std::string required = R"(["key1", "key3"])";
  const std::string schema = R"({"required": ["key1", "key3"]})";
  ASSERT_EQ(v.validate_required(_json_(json), _json_(required), _json_(schema)), false);
}
