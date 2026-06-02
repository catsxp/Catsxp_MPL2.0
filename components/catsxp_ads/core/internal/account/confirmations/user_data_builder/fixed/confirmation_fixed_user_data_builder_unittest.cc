/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/user_data_builder/fixed/confirmation_fixed_user_data_builder.h"

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/user_data_builder/test/confirmation_user_data_builder_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transactions_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsFixedUserDataBuilderTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    test::MockConfirmationUserData();

    AdvanceClockTo(test::TimeFromUTCString("November 18 2020 12:34:56.789"));
  }
};

TEST_F(CatsxpAdsFixedUserDataBuilderTest, BuildFixedUserData) {
  // Arrange
  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "buildChannel": "release",
                      "catalog": [
                        {
                          "id": "29e5c8bc0ba319069980bb390d8e8f9b58c05a20"
                        }
                      ],
                      "countryCode": "US",
                      "createdAtTimestamp": "2020-11-18T12:00:00.000Z",
                      "platform": "windows",
                      "rotatingHash": "I6KM54gXOrWqRHyrD518LmhePLHpIk4KSgCKOl0e3sc=",
                      "segment": "untargeted",
                      "studies": [],
                      "versionNumber": "1.2.0.0"
                    })JSON"),
            BuildFixedUserData(transaction));
}

TEST_F(CatsxpAdsFixedUserDataBuilderTest, BuildFixedUserDataForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "buildChannel": "release",
                      "countryCode": "US",
                      "platform": "windows",
                      "versionNumber": "1.2.0.0"
                    })JSON"),
            BuildFixedUserData(transaction));
}

}  // namespace catsxp_ads
