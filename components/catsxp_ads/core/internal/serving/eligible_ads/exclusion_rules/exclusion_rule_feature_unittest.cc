/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsExclusionRuleFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kExclusionRulesFeature));
}

TEST(CatsxpAdsExclusionRuleFeatureTest,
     ShouldExcludeAdIfDismissedWithinTimeWindow) {
  // Act & Assert
  EXPECT_EQ(base::Hours(0), kShouldExcludeAdIfDismissedWithinTimeWindow.Get());
}

TEST(CatsxpAdsExclusionRuleFeatureTest,
     ShouldExcludeAdIfLandedOnPageWithinTimeWindow) {
  // Act & Assert
  EXPECT_EQ(base::Hours(0),
            kShouldExcludeAdIfLandedOnPageWithinTimeWindow.Get());
}

TEST(CatsxpAdsExclusionRuleFeatureTest,
     ShouldExcludeAdIfCreativeInstanceExceedsPerHourCap) {
  // Act & Assert
  EXPECT_EQ(1U, kShouldExcludeAdIfCreativeInstanceExceedsPerHourCap.Get());
}

TEST(CatsxpAdsExclusionRuleFeatureTest,
     ShouldExcludeAdIfCreativeSetExceedsConversionCap) {
  // Act & Assert
  EXPECT_EQ(0U, kShouldExcludeAdIfCreativeSetExceedsConversionCap.Get());
}

}  // namespace catsxp_ads
