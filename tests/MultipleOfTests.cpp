#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(MultipleOf, NonNumber)
{
  ValidatorImpl v;
  const std::string json = R"([])";
  const std::string multipleOf = R"(5)";
  const std::string schema = R"({"multipleOf": 5})";
  ASSERT_EQ(v.validate_multipleOf(_json_(json), _json_(multipleOf), _json_(schema)), true);
}

TEST(MultipleOf, IntSuccess)
{
  ValidatorImpl v;
  const std::string json = R"(6)";
  const std::string multipleOf = R"(2)";
  const std::string schema = R"({"multipleOf": 2})";
  ASSERT_EQ(v.validate_multipleOf(_json_(json), _json_(multipleOf), _json_(schema)), true);
}

TEST(MultipleOf, IntFailure)
{
  ValidatorImpl v;
  const std::string json = R"(4)";
  const std::string multipleOf = R"(3)";
  const std::string schema = R"({"multipleOf": 3})";
  ASSERT_EQ(v.validate_multipleOf(_json_(json), _json_(multipleOf), _json_(schema)), false);
}

TEST(MultipleOf, FloatSuccess)
{
  ValidatorImpl v;
  const std::string json = R"(3.5)";
  const std::string multipleOf = R"(0.5)";
  const std::string schema = R"({"multipleOf": 0.5})";
  ASSERT_EQ(v.validate_multipleOf(_json_(json), _json_(multipleOf), _json_(schema)), true);
}

TEST(MultipleOf, FloatFailure)
{
  ValidatorImpl v;
  const std::string json = R"(3.3)";
  const std::string multipleOf = R"(0.2)";
  const std::string schema = R"({"multipleOf": 0.2})";
  ASSERT_EQ(v.validate_multipleOf(_json_(json), _json_(multipleOf), _json_(schema)), false);
}

TEST(MultipleOf, CombinedSuccess)
{
  ValidatorImpl v;
  const std::string json = R"(3)";
  const std::string multipleOf = R"(0.5)";
  const std::string schema = R"({"multipleOf": 0.5})";
  ASSERT_EQ(v.validate_multipleOf(_json_(json), _json_(multipleOf), _json_(schema)), true);
}
