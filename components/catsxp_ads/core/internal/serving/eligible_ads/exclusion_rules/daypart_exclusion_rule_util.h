/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_DAYPART_EXCLUSION_RULE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_DAYPART_EXCLUSION_RULE_UTIL_H_

namespace catsxp_ads {

struct CreativeDaypartInfo;

bool MatchDayOfWeek(const CreativeDaypartInfo& daypart, int day_of_week);

bool MatchTimeSlot(const CreativeDaypartInfo& daypart, int minutes);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_DAYPART_EXCLUSION_RULE_UTIL_H_
