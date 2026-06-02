/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/segment_user_data.h"

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transactions_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsSegmentUserDataTest : public test::TestBase {};

TEST_F(CatsxpAdsSegmentUserDataTest, BuildSegmentUserData) {
  // Arrange
  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "segment": "untargeted"
                    })JSON"),
            BuildSegmentUserData(transaction));
}

TEST_F(CatsxpAdsSegmentUserDataTest, DoNotBuildSearchResultAdSegmentUserData) {
  // Arrange
  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kSearchResultAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);

  // Act & Assert
  EXPECT_THAT(BuildSegmentUserData(transaction), ::testing::IsEmpty());
}

TEST_F(CatsxpAdsSegmentUserDataTest,
       DoNotBuildSegmentUserDataForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);

  // Act & Assert
  EXPECT_THAT(BuildSegmentUserData(transaction), ::testing::IsEmpty());
}

TEST_F(CatsxpAdsSegmentUserDataTest, DoNotBuildSegmentUserDataIfNoSegment) {
  // Arrange
  TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);
  transaction.segment = "";

  // Act & Assert
  EXPECT_THAT(BuildSegmentUserData(transaction), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
