#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(MaxLength, NonString)
{
  ValidatorImpl v;
  const std::string json = R"({})";
  const std::string maxLength = R"(0)";
  const std::string schema = R"({"maxLength": 0})";
  ASSERT_EQ(v.validate_maxLength(_json_(json), _json_(maxLength), _json_(schema)), true);
}

TEST(MaxLength, Empty)
{
  ValidatorImpl v;
  const std::string json = R"("")";
  const std::string maxLength = R"(0)";
  const std::string schema = R"({"maxLength": 0})";
  ASSERT_EQ(v.validate_maxLength(_json_(json), _json_(maxLength), _json_(schema)), true);
}

TEST(MaxLength, ExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"("123")";
  const std::string maxLength = R"(4)";
  const std::string schema = R"({"maxLength": 4})";
  ASSERT_EQ(v.validate_maxLength(_json_(json), _json_(maxLength), _json_(schema)), true);
}

TEST(MaxLength, NonExclusiveSuccess)
{
  ValidatorImpl v;
  const std::string json = R"("1234")";
  const std::string maxLength = R"(4)";
  const std::string schema = R"({"maxLength": 4})";
  ASSERT_EQ(v.validate_maxLength(_json_(json), _json_(maxLength), _json_(schema)), true);
}

TEST(MaxLength, Failure)
{
  ValidatorImpl v;
  const std::string json = R"("1234")";
  const std::string maxLength = R"(3)";
  const std::string schema = R"({"maxLength": 3})";
  ASSERT_EQ(v.validate_maxLength(_json_(json), _json_(maxLength), _json_(schema)), false);
}
