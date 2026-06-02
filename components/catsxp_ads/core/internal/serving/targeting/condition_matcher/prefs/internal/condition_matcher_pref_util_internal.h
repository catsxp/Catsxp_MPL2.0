/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_PREFS_INTERNAL_CONDITION_MATCHER_PREF_UTIL_INTERNAL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_PREFS_INTERNAL_CONDITION_MATCHER_PREF_UTIL_INTERNAL_H_

#include <optional>
#include <string>
#include <string_view>

namespace base {
class DictValue;
class ListValue;
class Value;
}  // namespace base

// Internal helpers for pref path traversal, exposed here so that each traversal
// step can be unit-tested independently.

namespace catsxp_ads {

// Returns the string representation of `value`, or `std::nullopt` for dict,
// list, and binary types.
std::optional<std::string> MaybeToString(const base::Value& value);

// Returns the root pref value for `pref_path`, checking virtual prefs first,
// then profile prefs, then local state, or `std::nullopt` if not found.
std::optional<base::Value> MaybeGetRootPrefValue(
    const base::DictValue& virtual_prefs,
    const std::string& pref_path);

// Returns the dict entry at `path_component`, or `std::nullopt` if not found.
std::optional<base::Value> MaybeGetDictPrefValue(
    const base::DictValue& dict,
    std::string_view path_component);

// Returns the list element at integer index `path_component`. If
// `path_component` is a `time_period_storage[=<duration>]` pattern, returns the
// aggregated sum of entries within the duration instead. Returns `std::nullopt`
// if the path component is invalid or out of bounds.
std::optional<base::Value> MaybeGetListPrefValue(
    const base::ListValue& list,
    std::string_view path_component);

// Returns the child value at `path_component` within `pref_value`, or
// `std::nullopt` if `pref_value` is not a dict or list and cannot be traversed
// further.
std::optional<base::Value> MaybeGetNextPrefValue(
    const base::Value& pref_value,
    std::string_view path_component);

// Returns the value at `pref_path` by traversing each component separated by
// `|`, or `std::nullopt` if any component cannot be resolved.
std::optional<base::Value> MaybeGetPrefValue(
    const base::DictValue& virtual_prefs,
    std::string_view pref_path);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_PREFS_INTERNAL_CONDITION_MATCHER_PREF_UTIL_INTERNAL_H_
