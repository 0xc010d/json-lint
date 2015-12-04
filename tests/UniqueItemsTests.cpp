#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(UniqueItems, NonArray)
{
  ValidatorImpl v;
  const std::string json = R"(15)";
  const std::string uniqueItems = R"(true)";
  const std::string schema = R"({"uniqueItems": true})";
  ASSERT_EQ(v.validate_uniqueItems(_json_(json), _json_(uniqueItems), _json_(schema)), true);
}

TEST(UniqueItems, NonUniqueItems)
{
  ValidatorImpl v;
  const std::string json = R"([1, 2, 3, 5, 2])";
  const std::string uniqueItems = R"(false)";
  const std::string schema = R"({"uniqueItems": false})";
  ASSERT_EQ(v.validate_uniqueItems(_json_(json), _json_(uniqueItems), _json_(schema)), true);
}

TEST(UniqueItems, Success)
{
  ValidatorImpl v;
  const std::string json = R"([1, 2, 3, 4, 5])";
  const std::string uniqueItems = R"(true)";
  const std::string schema = R"({"uniqueItems": true})";
  ASSERT_EQ(v.validate_uniqueItems(_json_(json), _json_(uniqueItems), _json_(schema)), true);
}

TEST(UniqueItems, Failure)
{
  ValidatorImpl v;
  const std::string json = R"([1, 2, 3, 5, 2])";
  const std::string uniqueItems = R"(true)";
  const std::string schema = R"({"uniqueItems": true})";
  ASSERT_EQ(v.validate_uniqueItems(_json_(json), _json_(uniqueItems), _json_(schema)), false);
}
