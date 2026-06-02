/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmations_util.h"

#include <optional>

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/non_reward/test/non_reward_confirmation_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/queue/confirmation_queue_database_table.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/queue/queue_item/test/confirmation_queue_item_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/reward/reward_confirmation_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/reward/test/reward_confirmation_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/test/confirmation_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/test/token_generator_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConfirmationsUtilTest : public test::TestBase {
 protected:
  database::table::ConfirmationQueue confirmation_queue_database_table_;
};

TEST_F(CatsxpAdsConfirmationsUtilTest, IsRewardConfirmationValid) {
  // Arrange
  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_TRUE(IsValid(*confirmation));
}

TEST_F(CatsxpAdsConfirmationsUtilTest, IsNonRewardConfirmationValid) {
  // Arrange
  test::DisableCatsxpRewards();

  std::optional<ConfirmationInfo> confirmation =
      test::BuildNonRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_TRUE(IsValid(*confirmation));
}

TEST_F(CatsxpAdsConfirmationsUtilTest, IsConfirmationNotValid) {
  // Arrange
  const ConfirmationInfo confirmation;

  // Act & Assert
  EXPECT_FALSE(IsValid(confirmation));
}

}  // namespace catsxp_ads
