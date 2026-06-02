/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/prefs/internal/condition_matcher_keyword_path_component_util.h"

namespace catsxp_ads {

std::optional<std::string_view> MaybeParseKeywordPathComponentValue(
    std::string_view path_component,
    std::string_view keyword) {
  if (!path_component.starts_with(keyword)) {
    return std::nullopt;
  }
  std::string_view remainder = path_component.substr(keyword.size());
  if (remainder.empty()) {
    return remainder;
  }
  if (!remainder.starts_with('=')) {
    // Something follows the keyword but is not separated by '='.
    return std::nullopt;
  }
  return remainder.substr(1);
}

}  // namespace catsxp_ads
