/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/matchers/internal/epoch_operator_condition_matcher_util_internal.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsOperatorConditionMatcherUtilInternalTest : public test::TestBase {
};

TEST_F(CatsxpAdsOperatorConditionMatcherUtilInternalTest,
       DoNotParseNegativeDays) {
  // Act & Assert
  EXPECT_FALSE(MaybeParseDays("[T=]:-1"));
}

TEST_F(CatsxpAdsOperatorConditionMatcherUtilInternalTest, ParseDayZero) {
  // Act & Assert
  EXPECT_EQ(0, MaybeParseDays("[T=]:0"));
}

TEST_F(CatsxpAdsOperatorConditionMatcherUtilInternalTest, MaybeParseDays) {
  // Act & Assert
  EXPECT_EQ(7, MaybeParseDays("[T=]:7"));
}

TEST_F(CatsxpAdsOperatorConditionMatcherUtilInternalTest,
       DoNotParseNonIntegerDays) {
  // Act & Assert
  EXPECT_FALSE(MaybeParseDays("[T=]:1.5"));
}

TEST_F(CatsxpAdsOperatorConditionMatcherUtilInternalTest,
       DoNotParseMalformedDays) {
  // Act & Assert
  EXPECT_FALSE(MaybeParseDays("[T=]: 7 "));
}

TEST_F(CatsxpAdsOperatorConditionMatcherUtilInternalTest,
       DoNotParseInvalidDays) {
  // Act & Assert
  EXPECT_FALSE(MaybeParseDays("[T=]:seven"));
}

TEST_F(CatsxpAdsOperatorConditionMatcherUtilInternalTest, IsUnixEpochTimestamp) {
  // Act & Assert
  EXPECT_TRUE(IsUnixEpochTimestamp(0));
  EXPECT_TRUE(IsUnixEpochTimestamp(2147483647));
}

TEST_F(CatsxpAdsOperatorConditionMatcherUtilInternalTest,
       IsNotUnixEpochTimestamp) {
  // Act & Assert
  EXPECT_FALSE(IsUnixEpochTimestamp(-1));
  EXPECT_FALSE(IsUnixEpochTimestamp(2147483648));
  EXPECT_FALSE(IsUnixEpochTimestamp(
      13372214400000000 /* 1st October 2024 00:00:00 UTC */));
}

TEST_F(CatsxpAdsOperatorConditionMatcherUtilInternalTest, WindowsToUnixEpoch) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_EQ(1727740800,
            WindowsToUnixEpoch(
                13372214400000000 /* 1st October 2024 00:00:00 UTC */));
}

TEST_F(CatsxpAdsOperatorConditionMatcherUtilInternalTest,
       TimeDeltaSinceUnixEpoch) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_EQ(base::Days(2),
            TimeDeltaSinceEpoch(1727740800 /*1st October 2024 00:00:00 UTC*/));
}

TEST_F(CatsxpAdsOperatorConditionMatcherUtilInternalTest,
       TimeDeltaSinceWindowsEpoch) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_EQ(base::Days(2),
            TimeDeltaSinceEpoch(
                13372214400000000 /*1st October 2024 00:00:00.000 UTC*/));
}

TEST_F(CatsxpAdsOperatorConditionMatcherUtilInternalTest,
       ParseWindowsEpochTimeDelta) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_EQ(base::Days(2),
            MaybeParseTimeDelta(
                "13372214400000000" /*1st October 2024 00:00:00 UTC*/));
}

TEST_F(CatsxpAdsOperatorConditionMatcherUtilInternalTest,
       ParseUnixEpochWithFractionalSecondsTimeDelta) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_EQ(base::Days(2),
            MaybeParseTimeDelta(
                "1727740800.3237710" /*1st October 2024 00:00:00 UTC*/));
}

TEST_F(CatsxpAdsOperatorConditionMatcherUtilInternalTest,
       ParseUnixEpochTimeDelta) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_EQ(base::Days(2), MaybeParseTimeDelta(
                               "1727740800" /*1st October 2024 00:00:00 UTC*/));
}

TEST_F(CatsxpAdsOperatorConditionMatcherUtilInternalTest,
       ParseTimeStringTimeDelta) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_EQ(base::Days(2),
            MaybeParseTimeDelta(
                "2024-10-01T00:00:00Z" /*1st October 2024 00:00:00 UTC*/));
  EXPECT_EQ(
      base::Days(2),
      MaybeParseTimeDelta(
          "2024-10-01T00:00:00.000000Z" /*1st October 2024 00:00:00 UTC*/));
  EXPECT_EQ(base::Days(2),
            MaybeParseTimeDelta(
                "2024-10-01T00:00:00" /*1st October 2024 00:00:00 UTC*/));
  EXPECT_EQ(
      base::Days(2),
      MaybeParseTimeDelta(
          "2024-10-01T00:00:00.000000" /*1st October 2024 00:00:00 UTC*/));
  EXPECT_EQ(base::Days(2),
            MaybeParseTimeDelta(
                "2024-09-30T19:00:00-05:00" /*1st October 2024 00:00:00 UTC*/));
  EXPECT_EQ(base::Days(2),
            MaybeParseTimeDelta(
                "1 Oct 2024 00:00:00" /*1st October 2024 00:00:00 UTC*/));
  EXPECT_EQ(
      base::Days(2),
      MaybeParseTimeDelta(
          "1 Oct 2024 00:00:00.000000" /*1st October 2024 00:00:00 UTC*/));
  EXPECT_EQ(base::Days(2),
            MaybeParseTimeDelta(
                "30 Sept 2024 19:00:00 EST" /*1st October 2024 00:00:00 UTC*/));
}

TEST_F(CatsxpAdsOperatorConditionMatcherUtilInternalTest,
       DoNotMaybeParseTimeDelta) {
  // Act & Assert
  EXPECT_FALSE(MaybeParseTimeDelta("broken time"));
}

}  // namespace catsxp_ads
