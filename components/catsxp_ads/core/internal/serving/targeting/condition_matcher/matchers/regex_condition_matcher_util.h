/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_MATCHERS_REGEX_CONDITION_MATCHER_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_MATCHERS_REGEX_CONDITION_MATCHER_UTIL_H_

#include <string_view>

// Matches conditions against string prefs using RE2 regular expressions, for
// ads that need more expressive matching than wildcards allow, such as matching
// a specific locale, all evaluated locally with nothing leaving the device.

namespace catsxp_ads {

// Returns `true` if `condition` (an RE2 expression) partially matches `value`,
// or `false` if it is not valid.
bool MatchRegex(std::string_view value, std::string_view condition);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_MATCHERS_REGEX_CONDITION_MATCHER_UTIL_H_
