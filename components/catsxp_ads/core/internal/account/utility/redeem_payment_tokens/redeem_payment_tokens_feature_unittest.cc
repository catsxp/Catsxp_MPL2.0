/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_payment_tokens/redeem_payment_tokens_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsRedeemPaymentTokensFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kRedeemPaymentTokensFeature));
}

TEST(CatsxpAdsRedeemPaymentTokensFeatureTest, RedeemPaymentTokensAfter) {
  // Act & Assert
  EXPECT_EQ(base::Days(1), kRedeemPaymentTokensAfter.Get());
}

}  // namespace catsxp_ads
