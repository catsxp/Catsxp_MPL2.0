/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/deposits/non_cash_deposit.h"

#include "base/test/mock_callback.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsNonCashDepositTest : public test::TestBase {};

TEST_F(CatsxpAdsNonCashDepositTest, GetValue) {
  // Arrange
  NonCashDeposit deposit;

  // Act & Assert
  base::MockCallback<GetDepositCallback> callback;
  EXPECT_CALL(callback, Run(/*success=*/true, /*value=*/0.0));
  deposit.GetValue(test::kCreativeInstanceId, callback.Get());
}

}  // namespace catsxp_ads
