/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_payment_tokens/redeem_payment_tokens_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/prefs/pref_util.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsRedeemPaymentTokensUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsRedeemPaymentTokensUtilTest, SetNextTokenRedemptionAt) {
  // Arrange
  SetNextTokenRedemptionAt(test::DistantFuture());

  // Act & Assert
  EXPECT_FALSE(
      GetProfileTimePref(prefs::kNextPaymentTokenRedemptionAt).is_null());
}

TEST_F(CatsxpAdsRedeemPaymentTokensUtilTest, ScheduleNextTokenRedemptionAt) {
  // Act & Assert
  EXPECT_FALSE(ScheduleNextTokenRedemptionAt().is_null());
}

TEST_F(CatsxpAdsRedeemPaymentTokensUtilTest,
       CalculateDelayBeforeRedeemingTokens) {
  // Arrange
  SetNextTokenRedemptionAt(test::Now() + base::Days(1));

  // Act & Assert
  EXPECT_EQ(base::Days(1), CalculateDelayBeforeRedeemingTokens());
}

TEST_F(CatsxpAdsRedeemPaymentTokensUtilTest,
       CalculateDelayBeforeRedeemingTokensIfHasNotPreviouslyRedeemedTokens) {
  // Act & Assert
  EXPECT_FALSE(ScheduleNextTokenRedemptionAt().is_null());
}

TEST_F(CatsxpAdsRedeemPaymentTokensUtilTest,
       CalculateDelayBeforeRedeemingTokensIfShouldHaveRedeemedTokensInThePast) {
  // Arrange
  SetNextTokenRedemptionAt(test::DistantPast());

  // Act & Assert
  EXPECT_EQ(base::Minutes(1), CalculateDelayBeforeRedeemingTokens());
}

TEST_F(CatsxpAdsRedeemPaymentTokensUtilTest,
       CalculateMinimumDelayBeforeRedeemingTokens) {
  // Arrange
  SetNextTokenRedemptionAt(test::Now() + base::Milliseconds(1));

  // Act & Assert
  EXPECT_EQ(base::Minutes(1), CalculateDelayBeforeRedeemingTokens());
}

}  // namespace catsxp_ads
