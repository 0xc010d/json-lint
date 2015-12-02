#include <gtest/gtest.h>
#include <ValidatorImpl.h>
#include "_JsonHelper.h"

TEST(AdditionalItems, DisallowedNoItems)
{
  ValidatorImpl v;
  const std::string json = R"([1, 2, 3, 4, 5])";
  const std::string additionalItems = R"(false)";
  const std::string schema = R"({"additionalItems": false})";
  ASSERT_EQ(v.validate_additionalItems(_json_(json), _json_(additionalItems), _json_(schema)), true);
}

TEST(AdditionalItems, DisallowedItemsObject)
{
  ValidatorImpl v;
  const std::string json = R"([1, 2, 3, 4, 5])";
  const std::string additionalItems = R"(false)";
  const std::string schema = R"({"additionalItems": false, "items": {}})";
  ASSERT_EQ(v.validate_additionalItems(_json_(json), _json_(additionalItems), _json_(schema)), true);
}

TEST(AdditionalItems, Object)
{
  ValidatorImpl v;
  const std::string json = R"([1, 2, 3, 4, 5])";
  const std::string additionalItems = R"({})";
  const std::string schema = R"({"additionalItems": {}, "items": []})";
  ASSERT_EQ(v.validate_additionalItems(_json_(json), _json_(additionalItems), _json_(schema)), true);
}

TEST(AdditionalItems, Allowed)
{
  ValidatorImpl v;
  const std::string json = R"([1, 2, 3, 4, 5])";
  const std::string additionalItems = R"(true)";
  const std::string schema = R"({"additionalItems": true, "items": []})";
  ASSERT_EQ(v.validate_additionalItems(_json_(json), _json_(additionalItems), _json_(schema)), true);
}

TEST(AdditionalItems, DisallowedSuccess)
{
  ValidatorImpl v;
  const std::string json1 = R"([1, 2, 3])";
  const std::string json2 = R"([1, 2, 3, 4])";
  const std::string additionalItems = R"(false)";
  const std::string schema = R"({"additionalItems": false, "items":[{}, {}, {}, {}]})";
  ASSERT_EQ(v.validate_additionalItems(_json_(json1), _json_(additionalItems), _json_(schema)), true);
  ASSERT_EQ(v.validate_additionalItems(_json_(json2), _json_(additionalItems), _json_(schema)), true);
}

TEST(AdditionalItems, DisallowedFailure)
{
  ValidatorImpl v;
  const std::string json = R"([1, 2, 3, 4, 5])";
  const std::string additionalItems = R"(false)";
  const std::string schema = R"({"additionalItems": false, "items":[{}, {}, {}, {}]})";
  ASSERT_EQ(v.validate_additionalItems(_json_(json), _json_(additionalItems), _json_(schema)), false);
}
