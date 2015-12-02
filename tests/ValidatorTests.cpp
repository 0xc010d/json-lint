#include <gtest/gtest.h>
#include <Validator.h>

using namespace json11;

TEST(ValidatorTests, EmptySchema) {
  Json schema("{}"), json;
  Validator validator(schema);
  ASSERT_EQ(validator.validate(json), true);
}
