/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/tokens_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsTokensFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kAccountTokensFeature));
}

TEST(CatsxpAdsTokensFeatureTest, MinConfirmationTokens) {
  // Act & Assert
  EXPECT_EQ(20U, kMinConfirmationTokens.Get());
}

TEST(CatsxpAdsTokensFeatureTest, MaxConfirmationTokens) {
  // Act & Assert
  EXPECT_EQ(50U, kMaxConfirmationTokens.Get());
}

}  // namespace catsxp_ads
