#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(OneOf, Ambiguous)
{
  ValidatorImpl v;
  const std::string json1 = R"("test")";
  const std::string json2 = R"(15)";
  const std::string oneOf = R"([{"type": "string"}, {"type": "number"}])";
  const std::string schema = R"({"oneOf": [{"type": "string"}, {"type": "number"}]})";
  ASSERT_EQ(v.validate_oneOf(_json_(json1), _json_(oneOf), _json_(schema)), true);
  ASSERT_EQ(v.validate_oneOf(_json_(json2), _json_(oneOf), _json_(schema)), true);
}

TEST(OneOf, SuccessOneItem)
{
  ValidatorImpl v;
  const std::string json = R"("test")";
  const std::string oneOf = R"([{"pattern": ".{4}"}])";
  const std::string schema = R"({"oneOf": [{"pattern": ".{4}"}]})";
  ASSERT_EQ(v.validate_oneOf(_json_(json), _json_(oneOf), _json_(schema)), true);
}

TEST(OneOf, FailureTwoItems)
{
  ValidatorImpl v;
  const std::string json = R"("test")";
  const std::string oneOf = R"([{"type": "string"}, {"pattern": ".{4}"}])";
  const std::string schema = R"({"oneOf": [{"type": "string"}, {"pattern": ".{4}"}]})";
  ASSERT_EQ(v.validate_oneOf(_json_(json), _json_(oneOf), _json_(schema)), false);
}

TEST(OneOf, Failure)
{
  ValidatorImpl v;
  const std::string json = R"("test")";
  const std::string oneOf = R"([{"pattern": ".{2}"}, {"pattern": ".{3}"}])";
  const std::string schema = R"({"oneOf": [{"pattern": ".{2}"}, {"pattern": ".{3}"}]})";
  ASSERT_EQ(v.validate_oneOf(_json_(json), _json_(oneOf), _json_(schema)), false);
}
