/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/anti_targeting/anti_targeting_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsAntiTargetingFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kAntiTargetingFeature));
}

TEST(CatsxpAdsAntiTargetingFeatureTest, AntiTargetingResourceVersion) {
  // Act & Assert
  EXPECT_EQ(1, kAntiTargetingResourceVersion.Get());
}

}  // namespace catsxp_ads
