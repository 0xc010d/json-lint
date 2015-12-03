#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(MinProperties, NonObject)
{
  ValidatorImpl v;
  const std::string json = R"([])";
  const std::string minProperties = R"(0)";
  const std::string schema = R"({"minProperties": 0})";
  ASSERT_EQ(v.validate_minProperties(_json_(json), _json_(minProperties), _json_(schema)), true);
}

TEST(MinProperties, Empty)
{
  ValidatorImpl v;
  const std::string json = R"({})";
  const std::string minProperties = R"(0)";
  const std::string schema = R"({"minProperties": 0})";
  ASSERT_EQ(v.validate_minProperties(_json_(json), _json_(minProperties), _json_(schema)), true);
}

TEST(MinProperties, ExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"({"1": 1, "2": 2, "3": 3, "4": 4, "5": 5})";
  const std::string minProperties = R"(4)";
  const std::string schema = R"({"minProperties": 4})";
  ASSERT_EQ(v.validate_minProperties(_json_(json), _json_(minProperties), _json_(schema)), true);
}

TEST(MinProperties, NonExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"({"1": 1, "2": 2, "3": 3, "4": 4})";
  const std::string minProperties = R"(4)";
  const std::string schema = R"({"minProperties": 4})";
  ASSERT_EQ(v.validate_minProperties(_json_(json), _json_(minProperties), _json_(schema)), true);
}

TEST(MinProperties, Failure)
{
  ValidatorImpl v;
  const std::string json = R"({"1": 1, "2": 2})";
  const std::string minProperties = R"(3)";
  const std::string schema = R"({"minProperties": 3})";
  ASSERT_EQ(v.validate_minProperties(_json_(json), _json_(minProperties), _json_(schema)), false);
}
