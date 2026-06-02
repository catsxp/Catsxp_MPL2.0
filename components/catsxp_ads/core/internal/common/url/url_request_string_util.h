/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_URL_REQUEST_STRING_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_URL_REQUEST_STRING_UTIL_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

std::string UrlRequestToString(
    const mojom::UrlRequestInfoPtr& mojom_url_request);
std::string UrlRequestHeadersToString(
    const mojom::UrlRequestInfoPtr& mojom_url_request);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_URL_REQUEST_STRING_UTIL_H_
