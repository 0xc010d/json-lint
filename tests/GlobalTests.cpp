#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(Global, EmptySchema) {
  ValidatorImpl v;
  ASSERT_EQ(v.validate(_json_(R"("test")")), true);
  ASSERT_EQ(v.validate(_json_(R"({})")), true);
  ASSERT_EQ(v.validate(_json_(R"([])")), true);
  ASSERT_EQ(v.validate(_json_(R"(true)")), true);
  ASSERT_EQ(v.validate(_json_(R"(15)")), true);
  ASSERT_EQ(v.validate(_json_(R"([1,2,3,4.5,{"key": true}])")), true);
}

TEST(Global, UnknownValidator) {
  const std::string schema = R"({"unknownValidator": {}})";
  ValidatorImpl v(_json_(schema));
  ASSERT_EQ(v.validate(_json_(R"("test")")), true);
  ASSERT_EQ(v.validate(_json_(R"({})")), true);
  ASSERT_EQ(v.validate(_json_(R"([])")), true);
  ASSERT_EQ(v.validate(_json_(R"(true)")), true);
  ASSERT_EQ(v.validate(_json_(R"(15)")), true);
  ASSERT_EQ(v.validate(_json_(R"([1,2,3,4.5,{"key": true}])")), true);
}
