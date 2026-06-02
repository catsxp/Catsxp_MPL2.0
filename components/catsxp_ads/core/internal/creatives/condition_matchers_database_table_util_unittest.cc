/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/condition_matchers_database_table_util.h"

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/condition_matcher_util.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_all_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::database::table {

namespace {

constexpr char kConditionMatchersAsString[] =
    R"(Zm9vLmJhcnxiYXo=|W1Q9XTo3;cXV4LnF1dXg=|W1I8XToz)";

ConditionMatcherMap ConditionMatchers() {
  return {{/*pref_path*/ "foo.bar|baz", /*condition*/ "[T=]:7"},
          {/*pref_path*/ "qux.quux", /*condition*/ "[R<]:3"}};
}

}  // namespace

TEST(CatsxpAdsConditionMatchersDatabaseTableUtilTest,
     ConditionMatchersToString) {
  // Arrange
  const ConditionMatcherMap condition_matchers = ConditionMatchers();

  // Act & Assert
  EXPECT_EQ(kConditionMatchersAsString,
            ConditionMatchersToString(condition_matchers));
}

TEST(CatsxpAdsConditionMatchersDatabaseTableUtilTest,
     EmptyConditionMatchersToString) {
  // Act & Assert
  EXPECT_THAT(ConditionMatchersToString({}), ::testing::IsEmpty());
}

TEST(CatsxpAdsConditionMatchersDatabaseTableUtilTest,
     StringToConditionMatchers) {
  // Act & Assert
  EXPECT_EQ(ConditionMatchers(),
            StringToConditionMatchers(kConditionMatchersAsString));
}

TEST(CatsxpAdsConditionMatchersDatabaseTableUtilTest,
     IgnoreMalformedStringInConditionMatchers) {
  // Act & Assert
  EXPECT_THAT(StringToConditionMatchers(R"(malformed)"), ::testing::IsEmpty());
}

}  // namespace catsxp_ads::database::table
