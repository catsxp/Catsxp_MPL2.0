/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/created_at_timestamp_user_data.h"

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transactions_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsCreatedAtTimestampUserDataTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    AdvanceClockTo(test::TimeFromUTCString("November 18 2020 12:34:56.789"));
  }
};

TEST_F(CatsxpAdsCreatedAtTimestampUserDataTest,
       BuildCreatedAtTimestampUserData) {
  // Arrange
  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "createdAtTimestamp": "2020-11-18T12:00:00.000Z"
                    })JSON"),
            BuildCreatedAtTimestampUserData(transaction));
}

TEST_F(CatsxpAdsCreatedAtTimestampUserDataTest,
       DoNotBuildCreatedAtTimestampUserDataForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);

  // Act & Assert
  EXPECT_THAT(BuildCreatedAtTimestampUserData(transaction),
              ::testing::IsEmpty());
}

}  // namespace catsxp_ads
