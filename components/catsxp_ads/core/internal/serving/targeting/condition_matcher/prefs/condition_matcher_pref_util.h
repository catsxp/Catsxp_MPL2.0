/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_PREFS_CONDITION_MATCHER_PREF_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_PREFS_CONDITION_MATCHER_PREF_UTIL_H_

#include <optional>
#include <string>
#include <string_view>

namespace base {
class DictValue;
}  // namespace base

// Pref values are exposed as strings for condition matching, regardless of
// whether they are virtual, profile, or local state prefs.

namespace catsxp_ads {

// Returns the value at `pref_path` as a string, converting bool, integer, and
// double to their string representations. `pref_path` uses `|` as the path
// delimiter because both registered pref names and dict keys within pref values
// may contain dots. For example, "p3a.logs_constellation_prep" is a pref name
// and P3A histogram names such as "Catsxp.Core.BookmarkCount" appear as dict
// keys inside that pref. Using `.` as a delimiter would be ambiguous so
// `base::Value::Find*ByDottedPath` is not used as it would incorrectly split on
// those dots. Subsequent `|` separated segments traverse into dict or list
// typed pref values. Returns `std::nullopt` if the path is malformed or
// unknown, or a path component into a list is neither a keyword path component
// nor an integer index.
std::optional<std::string> MaybeGetPrefValueAsString(
    const base::DictValue& virtual_prefs,
    std::string_view pref_path);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_PREFS_CONDITION_MATCHER_PREF_UTIL_H_
