/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_url_request_builder_util.h"

#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_constants.h"
#include "third_party/abseil-cpp/absl/strings/str_format.h"

namespace catsxp_ads {

std::string BuildCatalogUrlPath() {
  return absl::StrFormat("/v%d/catalog", kCatalogVersion);
}

}  // namespace catsxp_ads
