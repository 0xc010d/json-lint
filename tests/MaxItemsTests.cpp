#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(MaxItems, NonArray)
{
  ValidatorImpl v;
  const std::string json = R"({})";
  const std::string maxItems = R"(0)";
  const std::string schema = R"({"maxItems": 0})";
  ASSERT_EQ(v.validate_maxItems(_json_(json), _json_(maxItems), _json_(schema)), true);
}

TEST(MaxItems, Empty)
{
  ValidatorImpl v;
  const std::string json = R"([])";
  const std::string maxItems = R"(0)";
  const std::string schema = R"({"maxItems": 0})";
  ASSERT_EQ(v.validate_maxItems(_json_(json), _json_(maxItems), _json_(schema)), true);
}

TEST(MaxItems, ExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"([1, 2, 3])";
  const std::string maxItems = R"(4)";
  const std::string schema = R"({"maxItems": 4})";
  ASSERT_EQ(v.validate_maxItems(_json_(json), _json_(maxItems), _json_(schema)), true);
}

TEST(MaxItems, NonExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"([1, 2, 3, 4])";
  const std::string maxItems = R"(4)";
  const std::string schema = R"({"maxItems": 4})";
  ASSERT_EQ(v.validate_maxItems(_json_(json), _json_(maxItems), _json_(schema)), true);
}

TEST(MaxItems, Failure)
{
  ValidatorImpl v;
  const std::string json = R"([1, 2, 3, 4])";
  const std::string maxItems = R"(3)";
  const std::string schema = R"({"maxItems": 3})";
  ASSERT_EQ(v.validate_maxItems(_json_(json), _json_(maxItems), _json_(schema)), false);
}
