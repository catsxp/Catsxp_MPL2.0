/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_PREFS_INTERNAL_CONDITION_MATCHER_KEYWORD_PATH_COMPONENT_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_PREFS_INTERNAL_CONDITION_MATCHER_KEYWORD_PATH_COMPONENT_UTIL_H_

#include <optional>
#include <string_view>

// Parses "keyword[=value]" path components used in condition matcher pref
// paths, allowing each keyword to carry an optional value after '='.

namespace catsxp_ads {

// Parses a "keyword[=value]" path component and returns the value portion,
// i.e. the text after '=', or an empty string_view if no '=' is present.
// Returns `std::nullopt` if `path_component` does not start with `keyword` or
// has trailing content that is not preceded by '='.
std::optional<std::string_view> MaybeParseKeywordPathComponentValue(
    std::string_view path_component,
    std::string_view keyword);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_PREFS_INTERNAL_CONDITION_MATCHER_KEYWORD_PATH_COMPONENT_UTIL_H_
