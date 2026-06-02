/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/queue/queue_item/confirmation_queue_item_builder.h"

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/non_reward/test/non_reward_confirmation_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/queue/queue_item/confirmation_queue_item_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/reward/test/reward_confirmation_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/test/confirmation_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/test/token_generator_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConfirmationQueueItemBuilderTest : public test::TestBase {};

TEST_F(CatsxpAdsConfirmationQueueItemBuilderTest,
       BuildRewardConfirmationQueueItem) {
  // Arrange
  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act
  const ConfirmationQueueItemInfo confirmation_queue_item =
      BuildConfirmationQueueItem(*confirmation, /*process_at=*/test::Now());

  // Assert
  EXPECT_THAT(confirmation_queue_item,
              ::testing::FieldsAre(*confirmation, /*process_at*/ test::Now(),
                                   /*retry_count*/ 0));
}

TEST_F(CatsxpAdsConfirmationQueueItemBuilderTest,
       BuildNonRewardConfirmationQueueItem) {
  // Arrange
  test::DisableCatsxpRewards();

  std::optional<ConfirmationInfo> confirmation =
      test::BuildNonRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act
  const ConfirmationQueueItemInfo confirmation_queue_item =
      BuildConfirmationQueueItem(*confirmation, /*process_at=*/test::Now());

  // Assert
  EXPECT_THAT(confirmation_queue_item,
              ::testing::FieldsAre(*confirmation, /*process_at*/ test::Now(),
                                   /*retry_count*/ 0));
}

}  // namespace catsxp_ads
