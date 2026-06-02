/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/reward/redeem_reward_confirmation_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/test/payment_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsRedeemRewardConfirmationUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsRedeemRewardConfirmationUtilTest, AddPaymentToken) {
  // Arrange
  const PaymentTokenInfo payment_token = test::BuildPaymentToken();

  // Act & Assert
  EXPECT_TRUE(MaybeAddPaymentToken(payment_token));
}

TEST_F(CatsxpAdsRedeemRewardConfirmationUtilTest,
       DoNotAddDuplicatePaymentToken) {
  // Arrange
  const PaymentTokenInfo payment_token = test::BuildPaymentToken();
  ASSERT_TRUE(MaybeAddPaymentToken(payment_token));

  // Act & Assert
  EXPECT_FALSE(MaybeAddPaymentToken(payment_token));
}
TEST_F(CatsxpAdsRedeemRewardConfirmationUtilTest, LogPaymentTokenStatus) {
  // Act & Assert
  EXPECT_CALL(ads_client_mock_, Log);

  LogPaymentTokenStatus();
}

}  // namespace catsxp_ads
