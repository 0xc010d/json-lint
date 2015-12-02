#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(Global, EmptySchema) {
  ValidatorImpl v;
  ASSERT_EQ(v.validate("test"), true);
  ASSERT_EQ(v.validate("{}"), true);
  ASSERT_EQ(v.validate("[]"), true);
  ASSERT_EQ(v.validate("true"), true);
  ASSERT_EQ(v.validate("15"), true);
  ASSERT_EQ(v.validate("[1,2,3,4.5,{\"key\": true}]"), true);
}

TEST(Global, UnknownValidator) {
  const std::string schema = R"({"unknownValidator": {}})";
  ValidatorImpl v(_json_(schema));
  ASSERT_EQ(v.validate("test"), true);
  ASSERT_EQ(v.validate("{}"), true);
  ASSERT_EQ(v.validate("[]"), true);
  ASSERT_EQ(v.validate("true"), true);
  ASSERT_EQ(v.validate("15"), true);
  ASSERT_EQ(v.validate("[1,2,3,4.5,{\"key\": true}]"), true);
}
