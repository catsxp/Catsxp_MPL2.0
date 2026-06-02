/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/summary_user_data.h"

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/test/payment_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsSummaryUserDataTest : public test::TestBase {};

TEST_F(CatsxpAdsSummaryUserDataTest, BuildSummaryUserData) {
  // Arrange
  PaymentTokenList payment_tokens;

  const PaymentTokenInfo payment_token_1 =
      test::BuildPaymentToken(mojom::ConfirmationType::kViewedImpression,
                              mojom::AdType::kNotificationAd);
  payment_tokens.push_back(payment_token_1);

  const PaymentTokenInfo payment_token_2 =
      test::BuildPaymentToken(mojom::ConfirmationType::kViewedImpression,
                              mojom::AdType::kNotificationAd);
  payment_tokens.push_back(payment_token_2);

  const PaymentTokenInfo payment_token_3 = test::BuildPaymentToken(
      mojom::ConfirmationType::kClicked, mojom::AdType::kNotificationAd);
  payment_tokens.push_back(payment_token_3);

  const PaymentTokenInfo payment_token_4 = test::BuildPaymentToken(
      mojom::ConfirmationType::kViewedImpression, mojom::AdType::kNewTabPageAd);
  payment_tokens.push_back(payment_token_4);

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "totals": [
                        {
                          "ad_format": "ad_notification",
                          "click": 1,
                          "view": 2
                        },
                        {
                          "ad_format": "new_tab_page_ad",
                          "view": 1
                        }
                      ]
                    }
                )JSON"),
            BuildSummaryUserData(payment_tokens));
}

TEST_F(CatsxpAdsSummaryUserDataTest,
       DoNotBuildSummaryUserDataForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  const PaymentTokenList payment_tokens = test::BuildPaymentTokens(/*count=*/3);

  // Act & Assert
  EXPECT_THAT(BuildSummaryUserData(payment_tokens), ::testing::IsEmpty());
}

TEST_F(CatsxpAdsSummaryUserDataTest, BuildSummaryUserDataIfNoPaymentTokens) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "totals": []
                    })JSON"),
            BuildSummaryUserData(/*payment_tokens=*/{}));
}

}  // namespace catsxp_ads
