/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsUserActivityFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kUserActivityFeature));
}

TEST(CatsxpAdsUserActivityFeatureTest, MaximumUserActivityEvents) {
  // Act & Assert
  EXPECT_EQ(3'600U, kMaximumUserActivityEvents.Get());
}

TEST(CatsxpAdsUserActivityFeatureTest, UserActivityTriggers) {
  // Act & Assert
  EXPECT_EQ(
      "0D0B14110D0B14110D0B14110D0B1411=-1.0;0D0B1411070707=-1.0;07070707=-1.0",
      kUserActivityTriggers.Get());
}

TEST(CatsxpAdsUserActivityFeatureTest, UserActivityTimeWindow) {
  // Act & Assert
  EXPECT_EQ(base::Minutes(15), kUserActivityTimeWindow.Get());
}

TEST(CatsxpAdsUserActivityFeatureTest, UserActivityThreshold) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, kUserActivityThreshold.Get());
}

}  // namespace catsxp_ads
