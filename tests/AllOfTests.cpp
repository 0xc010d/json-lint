#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(AllOf, Ambiguous)
{
  ValidatorImpl v;
  const std::string json = R"("test")";
  const std::string allOf = R"([{"type": "string"}, {"type": "number"}])";
  const std::string schema = R"({"allOf": [{"type": "string"}, {"type": "number"}]})";
  ASSERT_EQ(v.validate_allOf(_json_(json), _json_(allOf), _json_(schema)), false);
}

TEST(AllOf, Success)
{
  ValidatorImpl v;
  const std::string json = R"("test")";
  const std::string allOf = R"([{"type": "string"}, {"pattern": ".{4}"}])";
  const std::string schema = R"({"allOf": [{"type": "string"}, {"pattern": ".{4}"}]})";
  ASSERT_EQ(v.validate_allOf(_json_(json), _json_(allOf), _json_(schema)), true);
}

TEST(AllOf, SuccessThreeItems)
{
  ValidatorImpl v;
  const std::string json = R"("tes")";
  const std::string allOf = R"([{"type": "string"}, {"pattern": ".{2,4}"}, {"minLength":2}])";
  const std::string schema = R"({"allOf": [{"type": "string"}, {"pattern": ".{2,4}"}, {"minLength":2}]})";
  ASSERT_EQ(v.validate_allOf(_json_(json), _json_(allOf), _json_(schema)), true);
}

TEST(AllOf, Failure)
{
  ValidatorImpl v;
  const std::string json = R"("test")";
  const std::string allOf = R"([{"type": "string"}, {"pattern": ".{3}"}])";
  const std::string schema = R"({"allOf": [{"type": "string"}, {"pattern": ".{3}"}]})";
  ASSERT_EQ(v.validate_allOf(_json_(json), _json_(allOf), _json_(schema)), false);
}
