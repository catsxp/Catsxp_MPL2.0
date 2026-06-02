/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/test/daypart_exclusion_rule_test_util.h"

#include "base/check.h"
#include "base/time/time.h"

namespace catsxp_ads::test {

int ConvertHoursAndMinutesToTotalMinutes(int hours, int minutes) {
  CHECK(hours >= 0 && hours <= 23);
  CHECK(minutes >= 0 && minutes <= 59);

  return hours * static_cast<int>(base::Time::kMinutesPerHour) + minutes;
}

}  // namespace catsxp_ads::test
