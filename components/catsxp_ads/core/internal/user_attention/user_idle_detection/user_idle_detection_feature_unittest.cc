/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/user_attention/user_idle_detection/user_idle_detection_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsUserIdleDetectionFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kUserIdleDetectionFeature));
}

TEST(CatsxpAdsUserIdleDetectionFeatureTest, UserIdleDetectionThreshold) {
  // Act & Assert
  EXPECT_EQ(base::Seconds(5), kUserIdleDetectionThreshold.Get());
}

TEST(CatsxpAdsUserIdleDetectionFeatureTest, MaximumUserIdleDetectionTime) {
  // Act & Assert
  EXPECT_EQ(base::Seconds(0), kMaximumUserIdleDetectionTime.Get());
}

TEST(CatsxpAdsUserIdleDetectionFeatureTest, ShouldDetectScreenWasLocked) {
  // Act & Assert
  EXPECT_FALSE(kShouldDetectScreenWasLocked.Get());
}

}  // namespace catsxp_ads
