/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TIME_TIME_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TIME_TIME_UTIL_H_

namespace base {
class Time;
}  // namespace base

namespace catsxp_ads {

// Returns the number of minutes elapsed since local midnight for `time`.
int MinutesElapsedSinceLocalMidnight(base::Time time);

// Returns midnight on the first day of the previous calendar month in local
// time, e.g., 2020-10-01 00:00:00.000 local when now is in November 2020.
base::Time LocalTimeAtBeginningOfPreviousMonth();

// Returns 23:59:59.999 on the last day of the previous calendar month in local
// time, e.g., 2020-10-31 23:59:59.999 local when now is in November 2020.
base::Time LocalTimeAtEndOfPreviousMonth();

// Returns midnight on the first day of the current calendar month in local
// time, e.g., 2020-11-01 00:00:00.000 local when now is in November 2020.
base::Time LocalTimeAtBeginningOfThisMonth();

// Returns 23:59:59.999 on the last day of the current calendar month in local
// time, e.g., 2020-11-30 23:59:59.999 local when now is in November 2020.
base::Time LocalTimeAtEndOfThisMonth();

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TIME_TIME_UTIL_H_
