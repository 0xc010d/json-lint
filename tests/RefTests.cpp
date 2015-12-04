#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

using namespace json11;

TEST(Ref, WrongUri1)
{
  auto schema = _json_(R"({"key": "value"})");
  ValidatorImpl v(schema);
  std::string ref = "/some/path";
  Json refSchema;
  ASSERT_EQ(v.findRef(ref, refSchema), false);
}

TEST(Ref, WrongUri2)
{
  auto schema = _json_(R"({"key": "value"})");
  ValidatorImpl v(schema);
  std::string ref = "#path";
  Json refSchema;
  ASSERT_EQ(v.findRef(ref, refSchema), false);
}

TEST(Ref, WrongUri3)
{
  auto schema = _json_(R"({"key": "value"})");
  ValidatorImpl v(schema);
  std::string ref = "#/";
  Json refSchema;
  ASSERT_EQ(v.findRef(ref, refSchema), false);
}

TEST(Ref, RootSchema)
{
  auto schema = _json_(R"({"key": "value"})");
  ValidatorImpl v(schema);
  std::string ref = "#";
  Json refSchema;
  ASSERT_EQ(v.findRef(ref, refSchema), true);
  ASSERT_EQ(schema, refSchema);
}

TEST(Ref, NonExistent)
{
  auto schema = _json_(R"({"key": "value"})");
  ValidatorImpl v(schema);
  std::string ref = "#/test";
  Json refSchema;
  ASSERT_EQ(v.findRef(ref, refSchema), false);
}

TEST(Ref, ExistentNodeNonObject)
{
  auto schema = _json_(R"({"key": "value"})");
  ValidatorImpl v(schema);
  std::string ref = "#/key";
  Json refSchema;
  ASSERT_EQ(v.findRef(ref, refSchema), false);
}

TEST(Ref, ExistentNodeWrongUri)
{
  auto schema = _json_(R"({"key": {}})");
  ValidatorImpl v(schema);
  std::string ref = "#/key/";
  Json refSchema;
  ASSERT_EQ(v.findRef(ref, refSchema), false);
}

TEST(Ref, SuccessFirstLevel)
{
  auto schema = _json_(R"({"key": {}})");
  ValidatorImpl v(schema);
  std::string ref = "#/key";
  Json refSchema;
  ASSERT_EQ(v.findRef(ref, refSchema), true);
}

TEST(Ref, SuccessSecondLevel)
{
  auto schema = _json_(R"({"key1": {"key2": {}}})");
  ValidatorImpl v(schema);
  std::string ref = "#/key1/key2";
  Json refSchema;
  ASSERT_EQ(v.findRef(ref, refSchema), true);
}

TEST(Ref, FailureSecondLevel)
{
  auto schema = _json_(R"({"key1": {"key3": {}}})");
  ValidatorImpl v(schema);
  std::string ref = "#/key1/key2";
  Json refSchema;
  ASSERT_EQ(v.findRef(ref, refSchema), false);
}

TEST(Ref, FailureSecondLevelNonObject)
{
  auto schema = _json_(R"({"key1": {"key2": ""}})");
  ValidatorImpl v(schema);
  std::string ref = "#/key1/key2";
  Json refSchema;
  ASSERT_EQ(v.findRef(ref, refSchema), false);
}

TEST(Ref, ValidationSuccess)
{
  ValidatorImpl v(_json_(R"({"key1": {"key2": {"type": "string", "enum": ["string"]}}})"));
  std::string json = R"("string")";
  std::string ref = R"("#/key1/key2")";
  std::string schema = R"({"$ref": "#/key1/key2"})";
  Json refSchema;
  ASSERT_EQ(v.validate_$ref(_json_(json), _json_(ref), _json_(schema)), true);
}

TEST(Ref, ValidationFailure)
{
  ValidatorImpl v(_json_(R"({"key1": {"key2": {"type": "string", "enum": ["string"]}}})"));
  std::string json = R"("number")";
  std::string ref = R"("#/key1/key2")";
  std::string schema = R"({"$ref": "#/key1/key2"})";
  Json refSchema;
  ASSERT_EQ(v.validate_$ref(_json_(json), _json_(ref), _json_(schema)), false);
}
