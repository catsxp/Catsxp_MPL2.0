/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/calendar/calendar_util.h"

#include <array>

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

constexpr std::array<int, 12> kDaysInNonLeapYear = {
    31,  // January
    28,  // February
    31,  // March
    30,  // April
    31,  // May
    30,  // June
    31,  // July
    31,  // August
    30,  // September
    31,  // October
    30,  // November
    31   // December
};

constexpr std::array<int, 12> kDaysInLeapYear = {
    31,  // January
    29,  // February
    31,  // March
    30,  // April
    31,  // May
    30,  // June
    31,  // July
    31,  // August
    30,  // September
    31,  // October
    30,  // November
    31   // December
};

}  // namespace

TEST(CatsxpAdsCalendarUtilTest, DaysInMonth) {
  for (size_t i = 0U; i < kDaysInNonLeapYear.size(); ++i) {
    EXPECT_EQ(kDaysInNonLeapYear[i],
              DaysInMonth(/*year=*/2021, static_cast<int>(i + 1U)));
  }
}

TEST(CatsxpAdsCalendarUtilTest, DaysInMonthForLeapYear) {
  for (size_t i = 0U; i < kDaysInLeapYear.size(); ++i) {
    EXPECT_EQ(kDaysInLeapYear[i],
              DaysInMonth(/*year=*/2020, static_cast<int>(i + 1U)));
  }
}

TEST(CatsxpAdsCalendarUtilTest, DaysInMonthForCenturyNonLeapYear) {
  for (size_t i = 0U; i < kDaysInNonLeapYear.size(); ++i) {
    EXPECT_EQ(kDaysInNonLeapYear[i],
              DaysInMonth(/*year=*/2100, static_cast<int>(i + 1U)));
  }
}

TEST(CatsxpAdsCalendarUtilTest, DaysInMonthForQuadricentennialLeapYear) {
  for (size_t i = 0U; i < kDaysInLeapYear.size(); ++i) {
    EXPECT_EQ(kDaysInLeapYear[i],
              DaysInMonth(/*year=*/2000, static_cast<int>(i + 1U)));
  }
}

}  // namespace catsxp_ads
