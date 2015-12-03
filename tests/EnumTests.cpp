#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(Enum, Failure)
{
  ValidatorImpl v;
  const std::string json = R"("test")";
  const std::string _enum = R"(["qwer"])";
  const std::string schema = R"({"enum": ["qwer"]})";
  ASSERT_EQ(v.validate_enum(_json_(json), _json_(_enum), _json_(schema)), false);
}

TEST(Enum, Success)
{
  ValidatorImpl v;
  const std::string json = R"("test")";
  const std::string _enum = R"(["test"])";
  const std::string schema = R"({"enum": ["test"]})";
  ASSERT_EQ(v.validate_enum(_json_(json), _json_(_enum), _json_(schema)), true);
}

TEST(Enum, ObjectFailure)
{
  ValidatorImpl v;
  const std::string json = R"({"key": ["value1", "value2", false]})";
  const std::string _enum = R"([{"key": ["value1", "value2", true]}])";
  const std::string schema = R"({"enum": [{"key": ["value1", "value2", true]}]})";
  ASSERT_EQ(v.validate_enum(_json_(json), _json_(_enum), _json_(schema)), false);
}

TEST(Enum, ObjectSuccess)
{
  ValidatorImpl v;
  const std::string json = R"({"key": ["value1", "value2", true]})";
  const std::string _enum = R"([{"key": ["value1", "value2", true]}])";
  const std::string schema = R"({"enum": [{"key": ["value1", "value2", true]}]})";
  ASSERT_EQ(v.validate_enum(_json_(json), _json_(_enum), _json_(schema)), true);
}

TEST(Enum, Last)
{
  ValidatorImpl v;
  const std::string json = R"(false)";
  const std::string _enum = R"([1, 2, 3, false])";
  const std::string schema = R"({"enum": [1, 2, 3, false]})";
  ASSERT_EQ(v.validate_enum(_json_(json), _json_(_enum), _json_(schema)), true);
}
