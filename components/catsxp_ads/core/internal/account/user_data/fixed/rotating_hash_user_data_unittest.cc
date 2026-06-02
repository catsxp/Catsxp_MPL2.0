/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/rotating_hash_user_data.h"

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transactions_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_environment_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsRotatingHashUserDataTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    AdvanceClockTo(test::TimeFromUTCString("2 June 2022 11:00"));
  }
};

TEST_F(CatsxpAdsRotatingHashUserDataTest, BuildRotatingHashUserData) {
  // Arrange
  test::SetUpDeviceId();

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "rotatingHash": "j9D7eKSoPLYNfxkG2Mx+SbgKJ9hcKg1QwDB8B5qxlpk="
                    })JSON"),
            BuildRotatingHashUserData(transaction));
}

TEST_F(CatsxpAdsRotatingHashUserDataTest,
       DoNotBuildRotatingHashUserDataForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  test::SetUpDeviceId();

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);

  // Act & Assert
  EXPECT_THAT(BuildRotatingHashUserData(transaction), ::testing::IsEmpty());
}

TEST_F(CatsxpAdsRotatingHashUserDataTest,
       DoNotBuildRotatingHashUserDataIfMissingDeviceId) {
  // Arrange
  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);

  // Act & Assert
  EXPECT_THAT(BuildRotatingHashUserData(transaction), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
