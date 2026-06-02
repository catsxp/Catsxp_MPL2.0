/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/eligible_ads_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsEligibleAdFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kEligibleAdFeature));
}

TEST(CatsxpAdsEligibleAdFeatureTest, SiteHistoryMaxCount) {
  // Act & Assert
  EXPECT_EQ(5'000, kSiteHistoryMaxCount.Get());
}

TEST(CatsxpAdsEligibleAdFeatureTest, SiteHistoryRecentDayRange) {
  // Act & Assert
  EXPECT_EQ(180, kSiteHistoryRecentDayRange.Get());
}

}  // namespace catsxp_ads
