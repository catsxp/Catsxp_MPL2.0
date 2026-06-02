/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/time/time_util.h"

#include <string_view>

#include "catsxp/components/catsxp_ads/core/internal/common/test/scoped_timezone_for_testing.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/timezone_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

// Parameterized by timezone to verify that time utility functions return
// correct local-time values regardless of DST, hemisphere, or UTC offset.

class CatsxpAdsTimeUtilTest
    : public test::TestBase,
      public ::testing::WithParamInterface<std::string_view> {
 protected:
  const test::ScopedTimezoneForTesting scoped_timezone_{GetParam()};
};

INSTANTIATE_TEST_SUITE_P(CatsxpAdsTimezones,
                         CatsxpAdsTimeUtilTest,
                         test::kTimezones,
                         test::TimezoneTestParamName);

TEST_P(CatsxpAdsTimeUtilTest, MinutesElapsedSinceLocalMidnight) {
  // Arrange
  const base::Time time = test::TimeFromString("November 18 2020 12:34:56");

  // Act & Assert
  EXPECT_EQ((12 * base::Time::kMinutesPerHour) + 34,
            MinutesElapsedSinceLocalMidnight(time));
}

TEST_P(CatsxpAdsTimeUtilTest, MinutesElapsedSinceLocalMidnightAtMidnight) {
  // Arrange
  const base::Time time = test::TimeFromString("November 18 2020 00:00:00");

  // Act & Assert
  EXPECT_EQ(0, MinutesElapsedSinceLocalMidnight(time));
}

TEST_P(CatsxpAdsTimeUtilTest,
       MinutesElapsedSinceLocalMidnightOneMinuteBeforeMidnight) {
  // Arrange
  const base::Time time = test::TimeFromString("November 18 2020 23:59:59");

  // Act & Assert
  EXPECT_EQ(1439, MinutesElapsedSinceLocalMidnight(time));
}

TEST_P(CatsxpAdsTimeUtilTest,
       MinutesElapsedSinceLocalMidnightDuringDstSpringForward) {
  // Arrange: 01:30 in a daylight saving time spring-forward window (clocks jump
  // 01:00→03:00 in America/New_York on March 8 2020). `LocalExplode` normalises
  // the skipped hour, so the result must still be the truncated elapsed minutes
  // (90) with no rounding artifacts.
  const base::Time time = test::TimeFromString("March 8 2020 01:30:00");

  // Act & Assert
  EXPECT_EQ(90, MinutesElapsedSinceLocalMidnight(time));
}

TEST_P(CatsxpAdsTimeUtilTest, LocalTimeAtBeginningOfPreviousMonth) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("November 18 2020 12:34:56.789"));

  // Act & Assert
  EXPECT_EQ(test::TimeFromString("October 1 2020 00:00:00.000"),
            LocalTimeAtBeginningOfPreviousMonth());
}

TEST_P(CatsxpAdsTimeUtilTest, LocalTimeAtBeginningOfPreviousMonthOnTheCusp) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("January 1 2020 00:00:00.000"));

  // Act & Assert
  EXPECT_EQ(test::TimeFromString("December 1 2019 00:00:00.000"),
            LocalTimeAtBeginningOfPreviousMonth());
}

TEST_P(CatsxpAdsTimeUtilTest, LocalTimeAtEndOfPreviousMonth) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("November 18 2020 12:34:56.789"));

  // Act & Assert
  EXPECT_EQ(test::TimeFromString("October 31 2020 23:59:59.999"),
            LocalTimeAtEndOfPreviousMonth());
}

TEST_P(CatsxpAdsTimeUtilTest, LocalTimeAtEndOfPreviousMonthOnTheCusp) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("January 1 2020 00:00:00.000"));

  // Act & Assert
  EXPECT_EQ(test::TimeFromString("December 31 2019 23:59:59.999"),
            LocalTimeAtEndOfPreviousMonth());
}

TEST_P(CatsxpAdsTimeUtilTest, LocalTimeAtBeginningOfThisMonth) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("November 18 2020 12:34:56.789"));

  // Act & Assert
  EXPECT_EQ(test::TimeFromString("November 1 2020 00:00:00.000"),
            LocalTimeAtBeginningOfThisMonth());
}

TEST_P(CatsxpAdsTimeUtilTest, LocalTimeAtEndOfThisMonth) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("November 18 2020 12:34:56.789"));

  // Act & Assert
  EXPECT_EQ(test::TimeFromString("November 30 2020 23:59:59.999"),
            LocalTimeAtEndOfThisMonth());
}

TEST_P(CatsxpAdsTimeUtilTest,
       LocalTimeAtBeginningOfPreviousMonthDuringDstInNewYorkAndStdInAuckland) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("July 18 2020 12:34:56.789"));

  // Act & Assert
  EXPECT_EQ(test::TimeFromString("June 1 2020 00:00:00.000"),
            LocalTimeAtBeginningOfPreviousMonth());
}

TEST_P(CatsxpAdsTimeUtilTest,
       LocalTimeAtEndOfPreviousMonthDuringDstInNewYorkAndStdInAuckland) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("July 18 2020 12:34:56.789"));

  // Act & Assert
  EXPECT_EQ(test::TimeFromString("June 30 2020 23:59:59.999"),
            LocalTimeAtEndOfPreviousMonth());
}

TEST_P(CatsxpAdsTimeUtilTest, LocalTimeAtEndOfThisMonthDuringCommonYear) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("February 18 2019 12:34:56.789"));

  // Act & Assert
  EXPECT_EQ(test::TimeFromString("February 28 2019 23:59:59.999"),
            LocalTimeAtEndOfThisMonth());
}

TEST_P(CatsxpAdsTimeUtilTest, LocalTimeAtEndOfPreviousMonthDuringCommonYear) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("March 18 2019 12:34:56.789"));

  // Act & Assert
  EXPECT_EQ(test::TimeFromString("February 28 2019 23:59:59.999"),
            LocalTimeAtEndOfPreviousMonth());
}

TEST_P(CatsxpAdsTimeUtilTest, LocalTimeAtEndOfThisMonthDuringLeapYear) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("February 18 2020 12:34:56.789"));

  // Act & Assert
  EXPECT_EQ(test::TimeFromString("February 29 2020 23:59:59.999"),
            LocalTimeAtEndOfThisMonth());
}

TEST_P(CatsxpAdsTimeUtilTest, LocalTimeAtEndOfPreviousMonthDuringLeapYear) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("March 18 2020 12:34:56.789"));

  // Act & Assert
  EXPECT_EQ(test::TimeFromString("February 29 2020 23:59:59.999"),
            LocalTimeAtEndOfPreviousMonth());
}

TEST_P(CatsxpAdsTimeUtilTest,
       LocalTimeAtBeginningOfThisMonthDuringDstInNewYorkAndStdInAuckland) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("July 18 2020 12:34:56.789"));

  // Act & Assert
  EXPECT_EQ(test::TimeFromString("July 1 2020 00:00:00.000"),
            LocalTimeAtBeginningOfThisMonth());
}

TEST_P(CatsxpAdsTimeUtilTest,
       LocalTimeAtEndOfThisMonthDuringDstInNewYorkAndStdInAuckland) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("July 18 2020 12:34:56.789"));

  // Act & Assert
  EXPECT_EQ(test::TimeFromString("July 31 2020 23:59:59.999"),
            LocalTimeAtEndOfThisMonth());
}

}  // namespace catsxp_ads
