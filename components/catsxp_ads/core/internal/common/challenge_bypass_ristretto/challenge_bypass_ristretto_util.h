/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_CHALLENGE_BYPASS_RISTRETTO_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_CHALLENGE_BYPASS_RISTRETTO_UTIL_H_

#include <optional>
#include <string>
#include <utility>

#include "base/types/expected.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"

namespace catsxp_ads::cbr {

template <typename T, typename U = T>
std::optional<U> ValueOrLogError(base::expected<T, std::string> result) {
  if (!result.has_value()) {
    BLOG(0, "Challenge Bypass Ristretto Error: " << result.error());
    return std::nullopt;
  }
  return std::make_optional<U>(std::move(result).value());
}

}  // namespace catsxp_ads::cbr

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_CHALLENGE_BYPASS_RISTRETTO_UTIL_H_
