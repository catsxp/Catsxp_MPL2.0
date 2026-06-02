/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/permission_rule_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsPermissionRuleFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kPermissionRulesFeature));
}

TEST(CatsxpAdsPermissionRuleFeatureTest, ShouldOnlyServeAdsInWindowedMode) {
  // Act & Assert
  EXPECT_TRUE(kShouldOnlyServeAdsInWindowedMode.Get());
}

TEST(CatsxpAdsPermissionRuleFeatureTest,
     ShouldOnlyServeAdsWithValidInternetConnection) {
  // Act & Assert
  EXPECT_TRUE(kShouldOnlyServeAdsWithValidInternetConnection.Get());
}

TEST(CatsxpAdsPermissionRuleFeatureTest, ShouldOnlyServeAdsIfMediaIsNotPlaying) {
  // Act & Assert
  EXPECT_TRUE(kShouldOnlyServeAdsIfMediaIsNotPlaying.Get());
}

TEST(CatsxpAdsPermissionRuleFeatureTest, ShouldOnlyServeAdsIfBrowserIsActive) {
  // Act & Assert
  EXPECT_TRUE(kShouldOnlyServeAdsIfBrowserIsActive.Get());
}

TEST(CatsxpAdsPermissionRuleFeatureTest, DoNotDisturbFromHour) {
  // Act & Assert
  EXPECT_EQ(21, kDoNotDisturbFromHour.Get());
}

TEST(CatsxpAdsPermissionRuleFeatureTest, DoNotDisturbToHour) {
  // Act & Assert
  EXPECT_EQ(6, kDoNotDisturbToHour.Get());
}

}  // namespace catsxp_ads
