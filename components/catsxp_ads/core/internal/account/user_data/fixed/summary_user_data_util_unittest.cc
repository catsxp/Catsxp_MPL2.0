/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/summary_user_data_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/test/payment_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsSummaryUserDataUtilTest, BuildBucketsIfNoPaymentTokens) {
  // Act & Assert
  EXPECT_THAT(BuildAdTypeBuckets(/*payment_tokens=*/{}), ::testing::IsEmpty());
}

TEST(CatsxpAdsSummaryUserDataUtilTest, BuildBuckets) {
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

  // Act
  const AdTypeBucketMap ad_type_buckets = BuildAdTypeBuckets(payment_tokens);

  // Assert
  const AdTypeBucketMap expected_ad_type_buckets = {
      {mojom::AdType::kNotificationAd,
       {{mojom::ConfirmationType::kClicked, 1},
        {mojom::ConfirmationType::kViewedImpression, 2}}},
      {mojom::AdType::kNewTabPageAd,
       {{mojom::ConfirmationType::kViewedImpression, 1}}}};
  EXPECT_EQ(expected_ad_type_buckets, ad_type_buckets);
}

}  // namespace catsxp_ads
