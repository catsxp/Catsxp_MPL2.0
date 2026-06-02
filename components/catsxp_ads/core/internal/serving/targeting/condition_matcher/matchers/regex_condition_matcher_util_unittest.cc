/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/matchers/regex_condition_matcher_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsRegexConditionMatcherUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsRegexConditionMatcherUtilTest, MatchRegex) {
  // Act & Assert
  EXPECT_TRUE(MatchRegex("foo.baz.bar", "(foo|bar)"));
}

TEST_F(CatsxpAdsRegexConditionMatcherUtilTest, MatchEmptyRegex) {
  // Act & Assert
  EXPECT_TRUE(MatchRegex("", ""));
}

TEST_F(CatsxpAdsRegexConditionMatcherUtilTest, DoNotMatchRegex) {
  // Act & Assert
  EXPECT_FALSE(MatchRegex("foo.baz.bar", "(waldo|fred)"));
}

TEST_F(CatsxpAdsRegexConditionMatcherUtilTest, DoNotMatchMalformedRegex) {
  // Act & Assert
  EXPECT_FALSE(MatchRegex("foo.baz.bar", "* ?"));
}

}  // namespace catsxp_ads
