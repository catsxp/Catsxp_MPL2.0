/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/prefs/internal/condition_matcher_keyword_path_component_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "testing/gmock/include/gmock/gmock.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConditionMatcherKeywordPathComponentUtilTest
    : public test::TestBase {};

TEST_F(CatsxpAdsConditionMatcherKeywordPathComponentUtilTest,
       ParseValueForExactKeyword) {
  // Act & Assert
  EXPECT_THAT(MaybeParseKeywordPathComponentValue("keyword", "keyword"),
              ::testing::Optional(::testing::IsEmpty()));
}

TEST_F(CatsxpAdsConditionMatcherKeywordPathComponentUtilTest,
       ParseValueForKeywordWithEmptyValue) {
  // Act & Assert
  EXPECT_THAT(MaybeParseKeywordPathComponentValue("keyword=", "keyword"),
              ::testing::Optional(::testing::IsEmpty()));
}

TEST_F(CatsxpAdsConditionMatcherKeywordPathComponentUtilTest,
       ParseValueForKeywordWithValue) {
  // Act & Assert
  EXPECT_EQ("value",
            MaybeParseKeywordPathComponentValue("keyword=value", "keyword"));
}

TEST_F(CatsxpAdsConditionMatcherKeywordPathComponentUtilTest,
       DoNotParseValueWhenKeywordHasNoSeparator) {
  // Act & Assert
  EXPECT_FALSE(MaybeParseKeywordPathComponentValue("keywordvalue", "keyword"));
}

TEST_F(CatsxpAdsConditionMatcherKeywordPathComponentUtilTest,
       DoNotParseValueWhenKeywordDoesNotMatch) {
  // Act & Assert
  EXPECT_FALSE(
      MaybeParseKeywordPathComponentValue("other_keyword=value", "keyword"));
}

TEST_F(CatsxpAdsConditionMatcherKeywordPathComponentUtilTest,
       DoNotParseValueForEmptyPathComponent) {
  // Act & Assert
  EXPECT_FALSE(MaybeParseKeywordPathComponentValue("", "keyword"));
}

}  // namespace catsxp_ads
