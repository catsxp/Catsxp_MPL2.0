/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/reward/redeem_reward_confirmation_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsRedeemRewardConfirmationFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kRedeemRewardConfirmationFeature));
}

TEST(CatsxpAdsRedeemRewardConfirmationFeatureTest, FetchPaymentTokenAfter) {
  // Act & Assert
  EXPECT_EQ(base::Seconds(3), kFetchPaymentTokenAfter.Get());
}

}  // namespace catsxp_ads
