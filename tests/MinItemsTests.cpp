#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(MinItems, NonArray)
{
  ValidatorImpl v;
  const std::string json = R"({})";
  const std::string minItems = R"(0)";
  const std::string schema = R"({"minItems": 0})";
  ASSERT_EQ(v.validate_minItems(_json_(json), _json_(minItems), _json_(schema)), true);
}

TEST(MinItems, Empty)
{
  ValidatorImpl v;
  const std::string json = R"([])";
  const std::string minItems = R"(0)";
  const std::string schema = R"({"minItems": 0})";
  ASSERT_EQ(v.validate_minItems(_json_(json), _json_(minItems), _json_(schema)), true);
}

TEST(MinItems, ExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"([1, 2, 3, 4, 5])";
  const std::string minItems = R"(4)";
  const std::string schema = R"({"minItems": 4})";
  ASSERT_EQ(v.validate_minItems(_json_(json), _json_(minItems), _json_(schema)), true);
}

TEST(MinItems, NonExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"([1, 2, 3, 4])";
  const std::string minItems = R"(4)";
  const std::string schema = R"({"minItems": 4})";
  ASSERT_EQ(v.validate_minItems(_json_(json), _json_(minItems), _json_(schema)), true);
}

TEST(MinItems, Failure)
{
  ValidatorImpl v;
  const std::string json = R"([1, 2])";
  const std::string minItems = R"(3)";
  const std::string schema = R"({"minItems": 3})";
  ASSERT_EQ(v.validate_minItems(_json_(json), _json_(minItems), _json_(schema)), false);
}
