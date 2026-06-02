/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/rotating_hash_user_data_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transactions_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_environment_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsRotatingHashUserDataUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsRotatingHashUserDataUtilTest,
       DoNotBuildRotatingHashIfMissingDeviceId) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("2 June 2022 11:00"));

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);

  // Act & Assert
  EXPECT_FALSE(BuildRotatingHash(transaction));
}

TEST_F(CatsxpAdsRotatingHashUserDataUtilTest, BuildRotatingHash) {
  // Arrange
  test::SetUpDeviceId();

  AdvanceClockTo(test::TimeFromUTCString("2 June 2022 11:00"));

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);

  // Act & Assert
  EXPECT_EQ("j9D7eKSoPLYNfxkG2Mx+SbgKJ9hcKg1QwDB8B5qxlpk=",
            BuildRotatingHash(transaction));
}

TEST_F(CatsxpAdsRotatingHashUserDataUtilTest,
       BuildRotatingHashIfWithinSameHour) {
  // Arrange
  test::SetUpDeviceId();

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);

  AdvanceClockTo(test::TimeFromUTCString("2 June 2022 11:00"));

  std::optional<std::string> rotating_hash_before =
      BuildRotatingHash(transaction);
  ASSERT_TRUE(rotating_hash_before);

  AdvanceClockBy(base::Hours(1) - base::Milliseconds(1));

  // Act & Assert
  EXPECT_EQ(rotating_hash_before, BuildRotatingHash(transaction));
}

TEST_F(CatsxpAdsRotatingHashUserDataUtilTest,
       BuildRotatingHashForDifferentHours) {
  // Arrange
  test::SetUpDeviceId();

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);

  AdvanceClockTo(test::TimeFromUTCString("2 June 2022 11:00"));

  std::optional<std::string> rotating_hash_before =
      BuildRotatingHash(transaction);
  ASSERT_TRUE(rotating_hash_before);

  AdvanceClockBy(base::Hours(1));

  // Act & Assert
  EXPECT_NE(rotating_hash_before, BuildRotatingHash(transaction));
}

TEST_F(CatsxpAdsRotatingHashUserDataUtilTest,
       BuildRotatingHashForSameHourButDifferentDay) {
  // Arrange
  test::SetUpDeviceId();

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);

  std::optional<std::string> rotating_hash_before =
      BuildRotatingHash(transaction);
  ASSERT_TRUE(rotating_hash_before);

  AdvanceClockBy(base::Days(1));

  // Act & Assert
  EXPECT_NE(rotating_hash_before, BuildRotatingHash(transaction));
}

}  // namespace catsxp_ads
