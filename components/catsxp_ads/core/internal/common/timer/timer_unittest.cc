/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/timer/timer.h"

#include "base/functional/callback_helpers.h"
#include "base/location.h"
#include "base/test/bind.h"
#include "base/test/gtest_util.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/random/test/scoped_rand_time_delta_with_jitter_for_testing.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsTimerTest : public test::TestBase {
 protected:
  Timer timer_;
};

TEST_F(CatsxpAdsTimerTest, IsNotRunningInitially) {
  // Act & Assert
  EXPECT_FALSE(timer_.IsRunning());
}

TEST_F(CatsxpAdsTimerTest, Start) {
  // Arrange
  const ScopedTimerDelaySetterForTesting scoped_delay(base::Seconds(7));

  // Act
  timer_.Start(FROM_HERE, base::Seconds(1), base::DoNothing());

  // Assert
  EXPECT_TRUE(timer_.IsRunning());
  EXPECT_EQ(base::Seconds(7), NextPendingTaskDelay());
}

TEST_F(CatsxpAdsTimerTest, StartRunsCallbackWhenDelayExpires) {
  // Arrange
  const ScopedTimerDelaySetterForTesting scoped_delay(base::Seconds(7));
  bool did_fire = false;

  // Act
  timer_.Start(FROM_HERE, base::Seconds(1),
               base::BindLambdaForTesting([&] { did_fire = true; }));
  ASSERT_TRUE(timer_.IsRunning());
  ASSERT_EQ(base::Seconds(7), NextPendingTaskDelay());
  FastForwardClockBy(base::Seconds(7));

  // Assert
  EXPECT_TRUE(did_fire);
  EXPECT_FALSE(timer_.IsRunning());
}

TEST_F(CatsxpAdsTimerTest, StartingAgainReplacesRunningTimer) {
  // Arrange
  const ScopedTimerDelaySetterForTesting scoped_delay(base::Seconds(7));

  int fire_count = 0;
  timer_.Start(FROM_HERE, base::Seconds(1),
               base::BindLambdaForTesting([&] { ++fire_count; }));

  // Act
  timer_.Start(FROM_HERE, base::Seconds(1),
               base::BindLambdaForTesting([&] { ++fire_count; }));
  FastForwardClockBy(base::Seconds(7));

  // Assert
  EXPECT_EQ(1, fire_count);
}

TEST_F(CatsxpAdsTimerTest, StartWithPrivacy) {
  // Arrange
  const ScopedTimerDelaySetterForTesting scoped_delay(base::Seconds(7));

  // Act
  timer_.StartWithPrivacy(FROM_HERE, base::Seconds(1), base::DoNothing());

  // Assert
  EXPECT_TRUE(timer_.IsRunning());
}

TEST_F(CatsxpAdsTimerTest, StartWithPrivacyRunsCallbackWhenDelayExpires) {
  // Arrange
  const ScopedTimerDelaySetterForTesting scoped_delay(base::Seconds(7));
  bool did_fire = false;

  // Act
  timer_.StartWithPrivacy(FROM_HERE, base::Seconds(1),
                          base::BindLambdaForTesting([&] { did_fire = true; }));
  ASSERT_TRUE(timer_.IsRunning());
  FastForwardClockBy(base::Seconds(7));

  // Assert
  EXPECT_TRUE(did_fire);
  EXPECT_FALSE(timer_.IsRunning());
}

TEST_F(CatsxpAdsTimerTest, StopReturnsTrueIfRunning) {
  // Arrange
  timer_.Start(FROM_HERE, base::Seconds(1), base::DoNothing());

  // Act & Assert
  EXPECT_TRUE(timer_.Stop());
}

TEST_F(CatsxpAdsTimerTest, StopPreventsTaskFromRunning) {
  // Arrange
  const ScopedTimerDelaySetterForTesting scoped_delay(base::Seconds(7));
  bool did_fire = false;
  timer_.Start(FROM_HERE, base::Seconds(1),
               base::BindLambdaForTesting([&] { did_fire = true; }));

  // Act
  timer_.Stop();
  FastForwardClockBy(base::Seconds(7));

  // Assert
  EXPECT_FALSE(did_fire);
}

TEST_F(CatsxpAdsTimerTest, StopReturnsFalseIfNotRunning) {
  // Act & Assert
  EXPECT_FALSE(timer_.Stop());
}

TEST_F(CatsxpAdsTimerTest, StartWithPrivacyChecksNegativeDelay) {
  // Arrange
  const test::ScopedRandTimeDeltaWithJitterForTesting
      scoped_rand_time_delta_with_jitter(base::Milliseconds(-1));

  // Act & Assert
  EXPECT_CHECK_DEATH(
      timer_.StartWithPrivacy(FROM_HERE, base::Seconds(10), base::DoNothing()));
}

}  // namespace catsxp_ads
