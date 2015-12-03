#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(Minimum, NonNumber)
{
  ValidatorImpl v;
  const std::string json = R"([])";
  const std::string minimum = R"(0)";
  const std::string schema = R"({"minimum": 0})";
  ASSERT_EQ(v.validate_minimum(_json_(json), _json_(minimum), _json_(schema)), true);
}

TEST(Minimum, ExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"(6)";
  const std::string minimum = R"(5)";
  const std::string schema = R"({"minimum": 5, "exclusiveMinimum": true})";
  ASSERT_EQ(v.validate_minimum(_json_(json), _json_(minimum), _json_(schema)), true);
}

TEST(Minimum, ExclusiveFailure)
{
  ValidatorImpl v;
  const std::string json = R"(4)";
  const std::string minimum = R"(4)";
  const std::string schema = R"({"minimum": 4, "exclusiveMinimum": true})";
  ASSERT_EQ(v.validate_minimum(_json_(json), _json_(minimum), _json_(schema)), false);
}

TEST(Minimum, NonExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"(4)";
  const std::string minimum = R"(4)";
  const std::string schema = R"({"minimum": 4, "exclusiveMinimum": false})";
  ASSERT_EQ(v.validate_minimum(_json_(json), _json_(minimum), _json_(schema)), true);
}

TEST(Minimum, NoExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"(4)";
  const std::string minimum = R"(4)";
  const std::string schema = R"({"minimum": 4})";
  ASSERT_EQ(v.validate_minimum(_json_(json), _json_(minimum), _json_(schema)), true);
}

TEST(Minimum, Failure)
{
  ValidatorImpl v;
  const std::string json = R"(3)";
  const std::string minimum = R"(4)";
  const std::string schema = R"({"minimum": 4})";
  ASSERT_EQ(v.validate_minimum(_json_(json), _json_(minimum), _json_(schema)), false);
}
