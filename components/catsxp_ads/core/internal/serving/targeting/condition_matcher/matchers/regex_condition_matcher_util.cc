/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/matchers/regex_condition_matcher_util.h"

#include "third_party/re2/src/re2/re2.h"

namespace catsxp_ads {

bool MatchRegex(std::string_view value, std::string_view condition) {
  const re2::RE2 re(condition, re2::RE2::Quiet);
  if (!re.ok()) {
    return false;
  }

  return re2::RE2::PartialMatch(value, re);
}

}  // namespace catsxp_ads
