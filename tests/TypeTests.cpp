#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(Type, Full)
{
  ValidatorImpl v;
  const std::string json1 = R"([])";
  const std::string json2 = R"({})";
  const std::string json3 = R"("str")";
  const std::string json4 = R"(15.2)";
  const std::string json5 = R"(7)";
  const std::string json6 = R"(true)";
  const std::string json7 = R"(null)";
  const std::string type = R"(["array", "object", "string", "number", "integer", "boolean", "null"])";
  const std::string schema = R"({"type": ["array", "object", "string", "number", "integer", "boolean", "null"]})";
  ASSERT_EQ(v.validate_type(_json_(json1), _json_(type), _json_(schema)), true);
  ASSERT_EQ(v.validate_type(_json_(json2), _json_(type), _json_(schema)), true);
  ASSERT_EQ(v.validate_type(_json_(json3), _json_(type), _json_(schema)), true);
  ASSERT_EQ(v.validate_type(_json_(json4), _json_(type), _json_(schema)), true);
  ASSERT_EQ(v.validate_type(_json_(json5), _json_(type), _json_(schema)), true);
  ASSERT_EQ(v.validate_type(_json_(json6), _json_(type), _json_(schema)), true);
  ASSERT_EQ(v.validate_type(_json_(json7), _json_(type), _json_(schema)), true);
}

TEST(Type, Array)
{
  ValidatorImpl v;
  const std::string json1 = R"([])";
  const std::string json2 = R"({})";
  const std::string type = R"("array")";
  const std::string schema = R"({"type": "array"})";
  ASSERT_EQ(v.validate_type(_json_(json1), _json_(type), _json_(schema)), true);
  ASSERT_EQ(v.validate_type(_json_(json2), _json_(type), _json_(schema)), false);
}

TEST(Type, Object)
{
  ValidatorImpl v;
  const std::string json1 = R"({})";
  const std::string json2 = R"([])";
  const std::string type = R"("object")";
  const std::string schema = R"({"type": "object"})";
  ASSERT_EQ(v.validate_type(_json_(json1), _json_(type), _json_(schema)), true);
  ASSERT_EQ(v.validate_type(_json_(json2), _json_(type), _json_(schema)), false);
}

TEST(Type, String)
{
  ValidatorImpl v;
  const std::string json1 = R"("")";
  const std::string json2 = R"([])";
  const std::string type = R"("string")";
  const std::string schema = R"({"type": "string"})";
  ASSERT_EQ(v.validate_type(_json_(json1), _json_(type), _json_(schema)), true);
  ASSERT_EQ(v.validate_type(_json_(json2), _json_(type), _json_(schema)), false);
}

TEST(Type, Number)
{
  ValidatorImpl v;
  const std::string json1 = R"(1.23)";
  const std::string json2 = R"(23)";
  const std::string json3 = R"("")";
  const std::string type = R"("number")";
  const std::string schema = R"({"type": "number"})";
  ASSERT_EQ(v.validate_type(_json_(json1), _json_(type), _json_(schema)), true);
  ASSERT_EQ(v.validate_type(_json_(json2), _json_(type), _json_(schema)), true);
  ASSERT_EQ(v.validate_type(_json_(json3), _json_(type), _json_(schema)), false);
}

TEST(Type, Integer)
{
  ValidatorImpl v;
  const std::string json1 = R"(15)";
  const std::string json2 = R"(15.0)";
  const std::string json3 = R"(123.45)";
  const std::string json4 = R"([])";
  const std::string type = R"("integer")";
  const std::string schema = R"({"type": "integer"})";
  ASSERT_EQ(v.validate_type(_json_(json1), _json_(type), _json_(schema)), true);
  ASSERT_EQ(v.validate_type(_json_(json2), _json_(type), _json_(schema)), true);
  ASSERT_EQ(v.validate_type(_json_(json3), _json_(type), _json_(schema)), false);
  ASSERT_EQ(v.validate_type(_json_(json4), _json_(type), _json_(schema)), false);
}

TEST(Type, Boolean)
{
  ValidatorImpl v;
  const std::string json1 = R"(true)";
  const std::string json2 = R"(false)";
  const std::string json3 = R"("true")";
  const std::string type = R"("boolean")";
  const std::string schema = R"({"type": "boolean"})";
  ASSERT_EQ(v.validate_type(_json_(json1), _json_(type), _json_(schema)), true);
  ASSERT_EQ(v.validate_type(_json_(json2), _json_(type), _json_(schema)), true);
  ASSERT_EQ(v.validate_type(_json_(json3), _json_(type), _json_(schema)), false);
}

TEST(Type, Null)
{
  ValidatorImpl v;
  const std::string json1 = R"(null)";
  const std::string json2 = R"([])";
  const std::string type = R"("null")";
  const std::string schema = R"({"type": "null"})";
  ASSERT_EQ(v.validate_type(_json_(json1), _json_(type), _json_(schema)), true);
  ASSERT_EQ(v.validate_type(_json_(json2), _json_(type), _json_(schema)), false);
}
