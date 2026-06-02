/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/matchers/pattern_condition_matcher_util.h"

#include "base/strings/pattern.h"

namespace catsxp_ads {

bool MatchPattern(std::string_view value, std::string_view condition) {
  return base::MatchPattern(value, condition);
}

}  // namespace catsxp_ads
