/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/url_request/subdivision_url_request_builder_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/url_request/subdivision_url_request_constants.h"
#include "third_party/abseil-cpp/absl/strings/str_format.h"

namespace catsxp_ads {

std::string BuildSubdivisionUrlPath() {
  return absl::StrFormat("/v%d/getstate", kSubdivisionServerVersion);
}

}  // namespace catsxp_ads
