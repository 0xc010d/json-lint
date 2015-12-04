#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(Pattern, NonString)
{
  ValidatorImpl v;
  const std::string json = R"(0)";
  const std::string pattern = R"(".{3}")";
  const std::string schema = R"({"pattern": ".{3}"})";
  ASSERT_EQ(v.validate_pattern(_json_(json), _json_(pattern), _json_(schema)), true);
}

TEST(Pattern, EmptyString)
{
  ValidatorImpl v;
  const std::string json = R"("")";
  const std::string pattern = R"(".{0}")";
  const std::string schema = R"({"pattern": ".{0}"})";
  ASSERT_EQ(v.validate_pattern(_json_(json), _json_(pattern), _json_(schema)), true);
}

TEST(Pattern, Success)
{
  ValidatorImpl v;
  const std::string json = R"("1234asdf")";
  const std::string pattern = R"("[\\d]{4}[\\D]+")";
  const std::string schema = R"({"pattern": "[\\d]{4}[\\D]+"})";
  ASSERT_EQ(v.validate_pattern(_json_(json), _json_(pattern), _json_(schema)), true);
}

TEST(Pattern, Failure)
{
  ValidatorImpl v;
  const std::string json = R"("asdf")";
  const std::string pattern = R"("[\\d]+")";
  const std::string schema = R"({"pattern": "[\\d]+"})";
  ASSERT_EQ(v.validate_pattern(_json_(json), _json_(pattern), _json_(schema)), false);
}
