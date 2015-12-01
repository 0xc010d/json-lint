#include <gtest/gtest.h>
#include <Validator.h>

TEST(ValidatorTests, EmptySchema) {
  Json schema("{}"), json;
  Validator validator(schema);
  ASSERT_EQ(validator.validate(json), true);
}
