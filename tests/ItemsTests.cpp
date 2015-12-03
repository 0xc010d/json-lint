#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(Items, NonArray)
{
  ValidatorImpl v;
  const std::string json = R"({})";
  const std::string items = R"(["qwer"])";
  const std::string schema = R"({"items": ["qwer"]})";
  ASSERT_EQ(v.validate_items(_json_(json), _json_(items), _json_(schema)), true);
}

TEST(Items, ObjectSuccess)
{
  ValidatorImpl v;
  const std::string json = R"(["test"])";
  const std::string items = R"({})";
  const std::string schema = R"({"items": {}})";
  ASSERT_EQ(v.validate_items(_json_(json), _json_(items), _json_(schema)), true);
}

TEST(Items, ObjectFailure)
{
  ValidatorImpl v;
  const std::string json = R"([false, "test"])";
  const std::string items = R"({"type": "boolean"})";
  const std::string schema = R"({"items": {"type": "boolean"}})";
  ASSERT_EQ(v.validate_items(_json_(json), _json_(items), _json_(schema)), false);
}

TEST(Items, ArraySuccess)
{
  ValidatorImpl v;
  const std::string json = R"(["test"])";
  const std::string items = R"([{}])";
  const std::string schema = R"({"items": [{}]})";
  ASSERT_EQ(v.validate_items(_json_(json), _json_(items), _json_(schema)), true);
}

TEST(Items, ArrayFailure)
{
  ValidatorImpl v;
  const std::string json = R"(["test", 1])";
  const std::string items = R"([{"type": "string"}, {"type": "string"}])";
  const std::string schema = R"({"items": [{"type": "string"}, {"type": "string"}]})";
  ASSERT_EQ(v.validate_items(_json_(json), _json_(items), _json_(schema)), false);
}

TEST(Items, EmptyArray)
{
  ValidatorImpl v;
  const std::string json1 = R"([])";
  const std::string json2 = R"([false])";
  const std::string items = R"([])";
  const std::string schema = R"({"items": []})";
  ASSERT_EQ(v.validate_items(_json_(json1), _json_(items), _json_(schema)), true);
  ASSERT_EQ(v.validate_items(_json_(json2), _json_(items), _json_(schema)), false);
}
