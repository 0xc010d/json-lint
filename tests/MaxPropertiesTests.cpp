#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(MaxProperties, NonObject)
{
  ValidatorImpl v;
  const std::string json = R"([])";
  const std::string maxProperties = R"(0)";
  const std::string schema = R"({"maxProperties": 0})";
  ASSERT_EQ(v.validate_maxProperties(_json_(json), _json_(maxProperties), _json_(schema)), true);
}

TEST(MaxProperties, Empty)
{
  ValidatorImpl v;
  const std::string json = R"({})";
  const std::string maxProperties = R"(0)";
  const std::string schema = R"({"maxProperties": 0})";
  ASSERT_EQ(v.validate_maxProperties(_json_(json), _json_(maxProperties), _json_(schema)), true);
}

TEST(MaxProperties, ExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"({"1": 1, "2": 2, "3": 3})";
  const std::string maxProperties = R"(4)";
  const std::string schema = R"({"maxProperties": 4})";
  ASSERT_EQ(v.validate_maxProperties(_json_(json), _json_(maxProperties), _json_(schema)), true);
}

TEST(MaxProperties, NonExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"({"1": 1, "2": 2, "3": 3, "4": 4})";
  const std::string maxProperties = R"(4)";
  const std::string schema = R"({"maxProperties": 4})";
  ASSERT_EQ(v.validate_maxProperties(_json_(json), _json_(maxProperties), _json_(schema)), true);
}

TEST(MaxProperties, Failure)
{
  ValidatorImpl v;
  const std::string json = R"({"1": 1, "2": 2, "3": 3, "4": 4})";
  const std::string maxProperties = R"(3)";
  const std::string schema = R"({"maxProperties": 3})";
  ASSERT_EQ(v.validate_maxProperties(_json_(json), _json_(maxProperties), _json_(schema)), false);
}
