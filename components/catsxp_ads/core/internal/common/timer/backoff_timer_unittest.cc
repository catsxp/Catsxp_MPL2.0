/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/timer/backoff_timer.h"

#include "base/functional/callback_helpers.h"
#include "base/location.h"
#include "base/test/bind.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/timer/timer.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsBackoffTimerTest : public test::TestBase {
 protected:
  BackoffTimer timer_;
};

TEST_F(CatsxpAdsBackoffTimerTest, IsNotRunningInitially) {
  // Act & Assert
  EXPECT_FALSE(timer_.IsRunning());
}

TEST_F(CatsxpAdsBackoffTimerTest, Start) {
  // Act
  timer_.Start(FROM_HERE, base::Seconds(1), base::DoNothing());

  // Assert
  EXPECT_TRUE(timer_.IsRunning());
  EXPECT_EQ(base::Seconds(1), NextPendingTaskDelay());
}

TEST_F(CatsxpAdsBackoffTimerTest, StartRunsCallbackWhenDelayExpires) {
  // Arrange
  bool did_fire = false;

  // Act
  timer_.Start(FROM_HERE, base::Seconds(1),
               base::BindLambdaForTesting([&] { did_fire = true; }));
  ASSERT_TRUE(timer_.IsRunning());
  ASSERT_EQ(base::Seconds(1), NextPendingTaskDelay());
  FastForwardClockBy(base::Seconds(1));

  // Assert
  EXPECT_TRUE(did_fire);
  EXPECT_FALSE(timer_.IsRunning());
}

TEST_F(CatsxpAdsBackoffTimerTest, StartingAgainReplacesRunningTimer) {
  // Arrange
  int fire_count = 0;
  timer_.Start(FROM_HERE, base::Seconds(1),
               base::BindLambdaForTesting([&] { ++fire_count; }));

  // Act
  timer_.Start(FROM_HERE, base::Seconds(1),
               base::BindLambdaForTesting([&] { ++fire_count; }));
  FastForwardClockBy(base::Seconds(1));

  // Assert
  EXPECT_EQ(1, fire_count);
}

TEST_F(CatsxpAdsBackoffTimerTest, StartDoesNotAccumulateBackoff) {
  // Arrange
  timer_.Start(FROM_HERE, base::Seconds(1), base::DoNothing());

  // Act
  timer_.Start(FROM_HERE, base::Seconds(1), base::DoNothing());

  // Assert
  EXPECT_EQ(base::Seconds(1), NextPendingTaskDelay());
}

TEST_F(CatsxpAdsBackoffTimerTest, StartWithPrivacy) {
  // Arrange
  const ScopedTimerDelaySetterForTesting scoped_delay(base::Seconds(7));

  // Act
  timer_.StartWithPrivacy(FROM_HERE, base::Seconds(1), base::DoNothing());

  // Assert
  EXPECT_TRUE(timer_.IsRunning());
}

TEST_F(CatsxpAdsBackoffTimerTest, StartWithPrivacyRunsCallbackWhenDelayExpires) {
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

TEST_F(CatsxpAdsBackoffTimerTest, StartWithPrivacyBacksOffExponentially) {
  // Act
  timer_.StartWithPrivacy(FROM_HERE, base::Seconds(1), base::DoNothing());
  timer_.Start(FROM_HERE, base::Seconds(1), base::DoNothing());

  // Assert
  ASSERT_EQ(base::Seconds(2), NextPendingTaskDelay());

  // Act
  timer_.StartWithPrivacy(FROM_HERE, base::Seconds(1), base::DoNothing());
  timer_.Start(FROM_HERE, base::Seconds(1), base::DoNothing());

  // Assert
  EXPECT_EQ(base::Seconds(4), NextPendingTaskDelay());
}

TEST_F(CatsxpAdsBackoffTimerTest, StartWithPrivacyDoesNotExceedMaxBackoffDelay) {
  // Arrange
  timer_.SetMaxBackoffDelay(base::Seconds(15));
  timer_.StartWithPrivacy(FROM_HERE, base::Seconds(10), base::DoNothing());

  // Act
  timer_.StartWithPrivacy(FROM_HERE, base::Seconds(10), base::DoNothing());
  timer_.Start(FROM_HERE, base::Seconds(10), base::DoNothing());

  // Assert
  EXPECT_EQ(base::Seconds(15), NextPendingTaskDelay());
}

TEST_F(CatsxpAdsBackoffTimerTest, StopResetsBackoff) {
  // Arrange
  timer_.StartWithPrivacy(FROM_HERE, base::Seconds(1), base::DoNothing());

  // Act
  timer_.Stop();
  timer_.Start(FROM_HERE, base::Seconds(1), base::DoNothing());

  // Assert
  EXPECT_EQ(base::Seconds(1), NextPendingTaskDelay());
}

TEST_F(CatsxpAdsBackoffTimerTest, StopResetsBackoffForStartWithPrivacy) {
  // Arrange
  const ScopedTimerDelaySetterForTesting scoped_delay(base::Seconds(1));
  timer_.StartWithPrivacy(FROM_HERE, base::Seconds(1), base::DoNothing());

  // Act
  timer_.Stop();
  timer_.StartWithPrivacy(FROM_HERE, base::Seconds(1), base::DoNothing());

  // Assert
  EXPECT_EQ(base::Seconds(1), NextPendingTaskDelay());
}

TEST_F(CatsxpAdsBackoffTimerTest, StopReturnsTrueIfRunning) {
  // Arrange
  timer_.Start(FROM_HERE, base::Seconds(1), base::DoNothing());

  // Act & Assert
  EXPECT_TRUE(timer_.Stop());
}

TEST_F(CatsxpAdsBackoffTimerTest, IsNotRunningAfterStop) {
  // Arrange
  timer_.Start(FROM_HERE, base::Seconds(1), base::DoNothing());

  // Act
  timer_.Stop();

  // Assert
  EXPECT_FALSE(timer_.IsRunning());
}

TEST_F(CatsxpAdsBackoffTimerTest, StopReturnsFalseIfNotRunning) {
  // Act & Assert
  EXPECT_FALSE(timer_.Stop());
}

}  // namespace catsxp_ads
