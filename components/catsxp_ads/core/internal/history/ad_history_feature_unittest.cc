/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/history/ad_history_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsAdHistoryFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kAdHistoryFeature));
}

TEST(CatsxpAdsAdHistoryFeatureTest, AdHistoryRetentionPeriod) {
  // Act & Assert
  EXPECT_EQ(base::Days(30), kAdHistoryRetentionPeriod.Get());
}

}  // namespace catsxp_ads
