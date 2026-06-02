/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsAdEventFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kAdEventFeature));
}

TEST(CatsxpAdsAdEventFeatureTest, DeduplicateViewedAdEventFor) {
  // Act & Assert
  EXPECT_EQ(base::Seconds(0), kDeduplicateViewedAdEventFor.Get());
}

TEST(CatsxpAdsAdEventFeatureTest, DeduplicateClickedAdEventFor) {
  // Act & Assert
  EXPECT_EQ(base::Seconds(1), kDeduplicateClickedAdEventFor.Get());
}

}  // namespace catsxp_ads
