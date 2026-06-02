/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/daypart_exclusion_rule_util.h"

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_daypart_info.h"

namespace catsxp_ads {

bool MatchDayOfWeek(const CreativeDaypartInfo& daypart, int day_of_week) {
  CHECK(day_of_week >= 0 && day_of_week <= 6);

  const char day_of_week_as_char = static_cast<char>('0' + day_of_week);
  return daypart.days_of_week.contains(day_of_week_as_char);
}

bool MatchTimeSlot(const CreativeDaypartInfo& daypart, int minutes) {
  return minutes >= daypart.start_minute && minutes <= daypart.end_minute;
}

}  // namespace catsxp_ads
