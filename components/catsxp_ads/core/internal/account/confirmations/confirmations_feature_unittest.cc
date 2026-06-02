/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmations_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsConfirmationsFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kConfirmationsFeature));
}

TEST(CatsxpAdsConfirmationsFeatureTest, ProcessConfirmationInitialBackoffDelay) {
  // Act & Assert
  EXPECT_EQ(base::Seconds(15), kProcessConfirmationInitialBackoffDelay.Get());
}

TEST(CatsxpAdsConfirmationsFeatureTest, ProcessConfirmationMaxBackoffDelay) {
  // Act & Assert
  EXPECT_EQ(base::Hours(6), kProcessConfirmationMaxBackoffDelay.Get());
}

}  // namespace catsxp_ads
