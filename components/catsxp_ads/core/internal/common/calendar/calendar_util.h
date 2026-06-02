/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CALENDAR_CALENDAR_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CALENDAR_CALENDAR_UTIL_H_

namespace catsxp_ads {

// Returns the number of days in `month` for `year`, accounting for leap years.
// Expects a 1-based month (1 = January, ..., 12 = December).
int DaysInMonth(int year, int month);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CALENDAR_CALENDAR_UTIL_H_
