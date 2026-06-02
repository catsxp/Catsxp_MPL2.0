/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/prefs/condition_matcher_pref_util.h"

#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/prefs/internal/condition_matcher_pref_util_internal.h"

namespace catsxp_ads {

std::optional<std::string> MaybeGetPrefValueAsString(
    const base::DictValue& virtual_prefs,
    std::string_view pref_path) {
  if (std::optional<base::Value> value =
          MaybeGetPrefValue(virtual_prefs, pref_path)) {
    return MaybeToString(*value);
  }

  // Unknown pref path.
  return std::nullopt;
}

}  // namespace catsxp_ads
