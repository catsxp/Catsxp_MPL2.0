/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/url_request/issuers_url_request_builder_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_constants.h"
#include "third_party/abseil-cpp/absl/strings/str_format.h"

namespace catsxp_ads {

std::string BuildIssuersUrlPath() {
  return absl::StrFormat("/v%d/issuers", kIssuersServerVersion);
}

}  // namespace catsxp_ads
