/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/random/random_util.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/random/test/scoped_rand_time_delta_with_jitter_for_testing.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsRandTimeDeltaWithJitterTest, ReturnsScopedValueWhenOverrideIsSet) {
  // Arrange
  const test::ScopedRandTimeDeltaWithJitterForTesting
      scoped_rand_time_delta_with_jitter(base::Seconds(7));

  // Act & Assert
  EXPECT_EQ(base::Seconds(7), RandTimeDeltaWithJitter(base::Minutes(42)));
}

TEST(CatsxpAdsRandTimeDeltaWithJitterTest,
     ReturnsValueInExpectedRangeWithoutOverride) {
  // Act
  const base::TimeDelta time_delta =
      RandTimeDeltaWithJitter(base::Seconds(100));

  // Assert
  EXPECT_GE(time_delta, base::Seconds(50));
  EXPECT_LT(time_delta, base::Seconds(150));
}

TEST(CatsxpAdsRandTimeDeltaWithJitterTest,
     ScopedOverrideIsRestoredAfterDestruction) {
  // Arrange
  {
    const test::ScopedRandTimeDeltaWithJitterForTesting
        scoped_rand_time_delta_with_jitter(base::Seconds(7));
  }

  // Act
  const base::TimeDelta time_delta =
      RandTimeDeltaWithJitter(base::Seconds(100));

  // Assert
  EXPECT_GE(time_delta, base::Seconds(50));
  EXPECT_LT(time_delta, base::Seconds(150));
}

}  // namespace catsxp_ads
