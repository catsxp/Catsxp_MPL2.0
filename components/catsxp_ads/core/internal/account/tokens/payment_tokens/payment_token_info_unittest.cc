/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/test/payment_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsPaymentTokenInfoTest : public test::TestBase {};

TEST_F(CatsxpAdsPaymentTokenInfoTest, IsValid) {
  // Act & Assert
  EXPECT_TRUE(test::BuildPaymentToken().IsValid());
}

TEST_F(CatsxpAdsPaymentTokenInfoTest, IsNotValid) {
  // Arrange
  const PaymentTokenInfo payment_token;

  // Act & Assert
  EXPECT_FALSE(payment_token.IsValid());
}

}  // namespace catsxp_ads
