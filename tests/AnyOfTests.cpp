#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(AnyOf, Ambiguous)
{
  ValidatorImpl v;
  const std::string json1 = R"("test")";
  const std::string json2 = R"(15)";
  const std::string anyOf = R"([{"type": "string"}, {"type": "number"}])";
  const std::string schema = R"({"anyOf": [{"type": "string"}, {"type": "number"}]})";
  ASSERT_EQ(v.validate_anyOf(_json_(json1), _json_(anyOf), _json_(schema)), true);
  ASSERT_EQ(v.validate_anyOf(_json_(json2), _json_(anyOf), _json_(schema)), true);
}

TEST(AnyOf, SuccessOneItem)
{
  ValidatorImpl v;
  const std::string json = R"("test")";
  const std::string anyOf = R"([{"pattern": ".{4}"}])";
  const std::string schema = R"({"anyOf": [{"pattern": ".{4}"}]})";
  ASSERT_EQ(v.validate_anyOf(_json_(json), _json_(anyOf), _json_(schema)), true);
}

TEST(AnyOf, SuccessTwoItems)
{
  ValidatorImpl v;
  const std::string json = R"("test")";
  const std::string anyOf = R"([{"type": "string"}, {"pattern": ".{4}"}])";
  const std::string schema = R"({"anyOf": [{"type": "string"}, {"pattern": ".{4}"}]})";
  ASSERT_EQ(v.validate_anyOf(_json_(json), _json_(anyOf), _json_(schema)), true);
}

TEST(AnyOf, SuccessThreeItems)
{
  ValidatorImpl v;
  const std::string json = R"("tes")";
  const std::string anyOf = R"([{"type": "string"}, {"pattern": ".{2,4}"}, {"minLength":2}])";
  const std::string schema = R"({"anyOf": [{"type": "string"}, {"pattern": ".{2,4}"}, {"minLength":2}]})";
  ASSERT_EQ(v.validate_anyOf(_json_(json), _json_(anyOf), _json_(schema)), true);
}

TEST(AnyOf, Failure)
{
  ValidatorImpl v;
  const std::string json = R"("test")";
  const std::string anyOf = R"([{"pattern": ".{2}"}, {"pattern": ".{3}"}])";
  const std::string schema = R"({"anyOf": [{"pattern": ".{2}"}, {"pattern": ".{3}"}]})";
  ASSERT_EQ(v.validate_anyOf(_json_(json), _json_(anyOf), _json_(schema)), false);
}
