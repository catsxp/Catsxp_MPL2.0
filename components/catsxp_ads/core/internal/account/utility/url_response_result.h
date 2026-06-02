/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_URL_RESPONSE_RESULT_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_URL_RESPONSE_RESULT_H_

#include <string>
#include <utility>

#include "base/types/expected.h"

namespace catsxp_ads {

struct UrlResponseErrorInfo {
  std::string message;
  bool should_retry = false;
};

template <typename T>
using UrlResponseResult = base::expected<T, UrlResponseErrorInfo>;

[[nodiscard]] inline base::unexpected<UrlResponseErrorInfo> UrlResponseError(
    UrlResponseErrorInfo error) {
  return base::unexpected(std::move(error));
}

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_URL_RESPONSE_RESULT_H_
