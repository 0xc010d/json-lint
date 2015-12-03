#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(Maximum, NonNumber)
{
  ValidatorImpl v;
  const std::string json = R"([])";
  const std::string maximum = R"(0)";
  const std::string schema = R"({"maximum": 0})";
  ASSERT_EQ(v.validate_maximum(_json_(json), _json_(maximum), _json_(schema)), true);
}

TEST(Maximum, ExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"(4)";
  const std::string maximum = R"(5)";
  const std::string schema = R"({"maximum": 5, "exclusiveMaximum": true})";
  ASSERT_EQ(v.validate_maximum(_json_(json), _json_(maximum), _json_(schema)), true);
}

TEST(Maximum, ExclusiveFailure)
{
  ValidatorImpl v;
  const std::string json = R"(4)";
  const std::string maximum = R"(4)";
  const std::string schema = R"({"maximum": 4, "exclusiveMaximum": true})";
  ASSERT_EQ(v.validate_maximum(_json_(json), _json_(maximum), _json_(schema)), false);
}

TEST(Maximum, NonExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"(4)";
  const std::string maximum = R"(4)";
  const std::string schema = R"({"maximum": 4, "exclusiveMaximum": false})";
  ASSERT_EQ(v.validate_maximum(_json_(json), _json_(maximum), _json_(schema)), true);
}

TEST(Maximum, NoExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"(4)";
  const std::string maximum = R"(4)";
  const std::string schema = R"({"maximum": 4})";
  ASSERT_EQ(v.validate_maximum(_json_(json), _json_(maximum), _json_(schema)), true);
}

TEST(Maximum, Failure)
{
  ValidatorImpl v;
  const std::string json = R"(5)";
  const std::string maximum = R"(4)";
  const std::string schema = R"({"maximum": 4})";
  ASSERT_EQ(v.validate_maximum(_json_(json), _json_(maximum), _json_(schema)), false);
}
