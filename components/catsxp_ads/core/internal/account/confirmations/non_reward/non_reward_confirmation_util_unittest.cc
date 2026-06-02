/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/non_reward/non_reward_confirmation_util.h"

#include <string_view>

#include "base/check.h"
#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/user_data_builder/confirmation_user_data_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/user_data_builder/test/confirmation_user_data_builder_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transaction_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transactions_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsNonRewardConfirmationUtilTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    test::MockConfirmationUserData();
  }
};

TEST_F(CatsxpAdsNonRewardConfirmationUtilTest, BuildNonRewardConfirmation) {
  // Arrange
  test::DisableCatsxpRewards();

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);

  // Act
  std::optional<ConfirmationInfo> confirmation =
      BuildNonRewardConfirmation(transaction, /*user_data=*/{});
  ASSERT_TRUE(confirmation);

  // Assert
  UserDataInfo expected_user_data;
  expected_user_data.fixed = base::test::ParseJsonDict(
      R"JSON(
          {
            "buildChannel": "release",
            "platform": "windows",
            "countryCode": "US",
            "versionNumber": "1.2.0.0"
          })JSON");

  EXPECT_THAT(
      *confirmation,
      ::testing::FieldsAre(test::kTransactionId, test::kCreativeInstanceId,
                           mojom::ConfirmationType::kViewedImpression,
                           mojom::AdType::kNotificationAd,
                           /*created_at*/ test::Now(),
                           /*reward*/ std::nullopt, expected_user_data));
}

TEST_F(CatsxpAdsNonRewardConfirmationUtilTest,
       DoNotBuildNonRewardConfirmationWithInvalidTransaction) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
#if CHECK_WILL_STREAM()
  constexpr std::string_view kFailureLog = "Check failed: transaction.IsValid*";
#else
  constexpr std::string_view kFailureLog = ".*";
#endif
  EXPECT_DEATH_IF_SUPPORTED(BuildNonRewardConfirmation(/*transaction=*/{},
                                                       /*user_data=*/{}),
                            kFailureLog);
}

TEST_F(CatsxpAdsNonRewardConfirmationUtilTest,
       DoNotBuildNonRewardConfirmationForRewardsUser) {
  // Arrange
  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);

  // Act & Assert
#if CHECK_WILL_STREAM()
  constexpr std::string_view kFailureLog =
      "Check failed: !UserHasJoinedCatsxpRewardsAndConnectedWallet*";
#else
  constexpr std::string_view kFailureLog = ".*";
#endif
  EXPECT_DEATH_IF_SUPPORTED(BuildNonRewardConfirmation(transaction,
                                                       /*user_data=*/{}),
                            kFailureLog);
}

}  // namespace catsxp_ads
