/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/matchers/pattern_condition_matcher_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsPatternConditionMatcherUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsPatternConditionMatcherUtilTest, MatchPattern) {
  // Act & Assert
  EXPECT_TRUE(MatchPattern("foo.baz.bar", "foo?baz.*"));
}

TEST_F(CatsxpAdsPatternConditionMatcherUtilTest, MatchEmptyPattern) {
  // Act & Assert
  EXPECT_TRUE(MatchPattern("", ""));
}

TEST_F(CatsxpAdsPatternConditionMatcherUtilTest, MatchEscapedPattern) {
  // Act & Assert
  EXPECT_TRUE(MatchPattern(R"(*.bar.?)", R"(\*.bar.\?)"));
}

TEST_F(CatsxpAdsPatternConditionMatcherUtilTest, DoNotMatchPattern) {
  // Act & Assert
  EXPECT_FALSE(MatchPattern("foo.baz.bar", "bar.*.foo"));
}

}  // namespace catsxp_ads
