/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/queue/queue_item/confirmation_queue_item_builder_util.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/random/test/scoped_rand_time_delta_with_jitter_for_testing.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConfirmationQueueItemBuilderUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsConfirmationQueueItemBuilderUtilTest,
       RetryProcessingConfirmationAfter) {
  // Arrange
  const test::ScopedRandTimeDeltaWithJitterForTesting
      scoped_rand_time_delta_with_jitter(base::Seconds(7));

  // Act
  const base::TimeDelta retry_processing_confirmation_after =
      RetryProcessingConfirmationAfter();

  // Assert
  EXPECT_EQ(base::Seconds(7), retry_processing_confirmation_after);
}

}  // namespace catsxp_ads
