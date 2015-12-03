#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(MinLength, NonString)
{
  ValidatorImpl v;
  const std::string json = R"({})";
  const std::string minLength = R"(0)";
  const std::string schema = R"({"minLength": 0})";
  ASSERT_EQ(v.validate_minLength(_json_(json), _json_(minLength), _json_(schema)), true);
}

TEST(MinLength, Empty)
{
  ValidatorImpl v;
  const std::string json = R"("")";
  const std::string minLength = R"(0)";
  const std::string schema = R"({"minLength": 0})";
  ASSERT_EQ(v.validate_minLength(_json_(json), _json_(minLength), _json_(schema)), true);
}

TEST(MinLength, ExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"("12345")";
  const std::string minLength = R"(4)";
  const std::string schema = R"({"minLength": 4})";
  ASSERT_EQ(v.validate_minLength(_json_(json), _json_(minLength), _json_(schema)), true);
}

TEST(MinLength, NonExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"("1234")";
  const std::string minLength = R"(4)";
  const std::string schema = R"({"minLength": 4})";
  ASSERT_EQ(v.validate_minLength(_json_(json), _json_(minLength), _json_(schema)), true);
}

TEST(MinLength, Failure)
{
  ValidatorImpl v;
  const std::string json = R"("12")";
  const std::string minLength = R"(3)";
  const std::string schema = R"({"minLength": 3})";
  ASSERT_EQ(v.validate_minLength(_json_(json), _json_(minLength), _json_(schema)), false);
}
