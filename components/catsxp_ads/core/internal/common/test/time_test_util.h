/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_TIME_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_TIME_TEST_UTIL_H_

#include <string>

namespace base {
class Time;
class TimeDelta;
}  // namespace base

namespace catsxp_ads::test {

// The distance between the past, present and future is only a persistent
// illusion. Albert Einstein.

base::Time DistantPast();
std::string DistantPastAsIso8601();

base::Time Now();
std::string NowAsIso8601();

base::Time DistantFuture();
std::string DistantFutureAsIso8601();

// Converts a string representation of time to a `base::Time` object.
base::Time TimeFromString(const std::string& time_string);

// Converts a string representation of UTC time to a `base::Time` object.
base::Time TimeFromUTCString(const std::string& time_string);

// Converts a string representation of time duration since now to a
// `base::TimeDelta` object.
base::TimeDelta TimeDeltaFromString(const std::string& time_string);

// Converts a string representation of time duration since UTC now to a
// `base::TimeDelta` object.
base::TimeDelta TimeDeltaFromUTCString(const std::string& time_string);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_TIME_TEST_UTIL_H_
