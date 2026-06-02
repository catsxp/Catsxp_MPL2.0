/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_tokens.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/test/payment_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsPaymentTokenUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsPaymentTokenUtilTest, AddPaymentTokens) {
  // Arrange
  const PaymentTokenList payment_tokens = test::BuildPaymentTokens(/*count=*/2);
  ASSERT_THAT(payment_tokens, ::testing::SizeIs(2));

  const PaymentTokenInfo& token_1 = payment_tokens.at(0);
  const PaymentTokenInfo& token_2 = payment_tokens.at(1);

  test::GetPaymentTokens().SetTokens({token_1});

  // Act
  AddPaymentTokens({token_2});

  // Assert
  const PaymentTokenList expected_payment_tokens = {token_1, token_2};
  EXPECT_EQ(expected_payment_tokens, GetAllPaymentTokens());
}

TEST_F(CatsxpAdsPaymentTokenUtilTest, PaymentTokenCount) {
  // Arrange
  test::SetPaymentTokens(/*count=*/3);

  // Act & Assert
  EXPECT_EQ(3U, PaymentTokenCount());
}

}  // namespace catsxp_ads
