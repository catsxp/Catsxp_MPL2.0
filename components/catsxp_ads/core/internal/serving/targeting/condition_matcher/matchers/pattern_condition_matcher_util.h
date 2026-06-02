/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_MATCHERS_PATTERN_CONDITION_MATCHER_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_MATCHERS_PATTERN_CONDITION_MATCHER_UTIL_H_

#include <string_view>

// Matches conditions against string prefs using wildcards, for ads that need
// exact, partial, prefix, or suffix matching without requiring full regular
// expression syntax, all evaluated locally with nothing leaving the device.

namespace catsxp_ads {

// Returns `true` if `value` matches `condition` as a full string. `*` matches
// zero or more characters, `?` matches exactly one character, and `\` escapes
// either literally.
bool MatchPattern(std::string_view value, std::string_view condition);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_MATCHERS_PATTERN_CONDITION_MATCHER_UTIL_H_
