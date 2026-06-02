/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_PREFS_INTERNAL_CONDITION_MATCHER_FEATURE_PREF_UTIL_INTERNAL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_PREFS_INTERNAL_CONDITION_MATCHER_FEATURE_PREF_UTIL_INTERNAL_H_

#include <optional>
#include <string_view>

namespace base {
class Value;
}  // namespace base

// Resolves `[virtual]:feature=<feature_name>` keyword path components into a
// dict whose sub-paths are traversed via the normal `|` separator. Any feature
// name is supported, including future ones not yet known at build time.

namespace catsxp_ads {

inline constexpr std::string_view kFeatureVirtualPrefKeyword =
    "[virtual]:feature";

// Returns a dict with an `is_overridden` string, either "1" if overridden or
// "0" if not; unknown feature names are treated as not overridden. When a
// field trial is associated the dict also contains a `params` sub-dict of
// param name-value pairs; otherwise `params` is absent and any
// `|params|<param_name>` traversal returns nothing. Returns `std::nullopt` if
// `path_component` does not match `[virtual]:feature=<feature_name>` or the
// feature name is empty.
std::optional<base::Value> MaybeGetFeaturePrefValue(
    std::string_view path_component);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_PREFS_INTERNAL_CONDITION_MATCHER_FEATURE_PREF_UTIL_INTERNAL_H_
