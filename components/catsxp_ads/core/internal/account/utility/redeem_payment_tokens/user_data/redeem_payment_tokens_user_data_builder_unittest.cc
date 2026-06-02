/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_payment_tokens/user_data/redeem_payment_tokens_user_data_builder.h"

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/test/payment_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsRedeemPaymentTokensUserDataBuilderTest : public test::TestBase {};

TEST_F(CatsxpAdsRedeemPaymentTokensUserDataBuilderTest, BuildUserData) {
  // Act & Assert
  EXPECT_EQ(
      base::test::ParseJsonDict(R"JSON(
          {
            "platform": "windows",
            "totals": [
              {
                "ad_format": "ad_notification",
                "view": 2
              }
            ]
          })JSON"),
      BuildRedeemPaymentTokensUserData(test::BuildPaymentTokens(/*count=*/2)));
}

}  // namespace catsxp_ads
