/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/daypart_exclusion_rule_util.h"

#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_daypart_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/test/daypart_exclusion_rule_test_util.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsDaypartExclusionRuleUtilTest, MatchDayOfWeek) {
  // Arrange
  CreativeDaypartInfo daypart;
  daypart.days_of_week = "0123456";

  // Act & Assert
  EXPECT_TRUE(MatchDayOfWeek(daypart, /*wednesday*/ 3));
}

TEST(CatsxpAdsDaypartExclusionRuleUtilTest, DoNotMatchDayOfWeek) {
  // Arrange
  CreativeDaypartInfo daypart;
  daypart.days_of_week = "012456";

  // Act & Assert
  EXPECT_FALSE(MatchDayOfWeek(daypart, /*wednesday*/ 3));
}

TEST(CatsxpAdsDaypartExclusionRuleUtilTest, MatchTimeSlot) {
  // Arrange
  CreativeDaypartInfo daypart;
  daypart.start_minute =
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/0, /*minutes=*/0);
  daypart.end_minute =
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/23, /*minutes=*/59);

  // Act & Assert
  EXPECT_TRUE(MatchTimeSlot(daypart, test::ConvertHoursAndMinutesToTotalMinutes(
                                         /*hours=*/5, /*minutes=*/35)));
}

TEST(CatsxpAdsDaypartExclusionRuleUtilTest, MatchExactTimeSlot) {
  // Arrange
  CreativeDaypartInfo daypart;
  daypart.start_minute =
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/5, /*minutes=*/35);
  daypart.end_minute =
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/5, /*minutes=*/35);

  // Act & Assert
  EXPECT_TRUE(MatchTimeSlot(daypart, test::ConvertHoursAndMinutesToTotalMinutes(
                                         /*hours=*/5, /*minutes=*/35)));
}

TEST(CatsxpAdsDaypartExclusionRuleUtilTest, DoNotMatchTimeSlotAfterEndMinute) {
  // Arrange
  CreativeDaypartInfo daypart;
  daypart.start_minute =
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/0, /*minutes=*/0);
  daypart.end_minute =
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/5, /*minutes=*/34);

  // Act & Assert
  EXPECT_FALSE(MatchTimeSlot(
      daypart,
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/5, /*minutes=*/35)));
}

TEST(CatsxpAdsDaypartExclusionRuleUtilTest,
     DoNotMatchTimeSlotBeforeStartMinute) {
  // Arrange
  CreativeDaypartInfo daypart;
  daypart.start_minute =
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/5, /*minutes=*/36);
  daypart.end_minute =
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/23, /*minutes=*/59);

  // Act & Assert
  EXPECT_FALSE(MatchTimeSlot(
      daypart,
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/5, /*minutes=*/35)));
}

}  // namespace catsxp_ads
