#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(Not, Success)
{
  ValidatorImpl v;
  const std::string json1 = R"([])";
  const std::string json2 = R"({})";
  const std::string json3 = R"(0)";
  const std::string json4 = R"(false)";
  const std::string json5 = R"(null)";
  const std::string _not = R"({"type": "string"})";
  const std::string schema = R"({"not": {"type": "string"}})";
  ASSERT_EQ(v.validate_not(_json_(json1), _json_(_not), _json_(schema)), true);
  ASSERT_EQ(v.validate_not(_json_(json2), _json_(_not), _json_(schema)), true);
  ASSERT_EQ(v.validate_not(_json_(json3), _json_(_not), _json_(schema)), true);
  ASSERT_EQ(v.validate_not(_json_(json4), _json_(_not), _json_(schema)), true);
  ASSERT_EQ(v.validate_not(_json_(json5), _json_(_not), _json_(schema)), true);
}

TEST(Not, Failure)
{
  ValidatorImpl v;
  const std::string json = R"({})";
  const std::string _not = R"({})";
  const std::string schema = R"({"not": {}})";
  ASSERT_EQ(v.validate_not(_json_(json), _json_(_not), _json_(schema)), false);
}
