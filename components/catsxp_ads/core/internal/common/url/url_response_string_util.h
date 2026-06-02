/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_URL_RESPONSE_STRING_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_URL_RESPONSE_STRING_UTIL_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

std::string UrlResponseToString(
    const mojom::UrlResponseInfo& mojom_url_response);
std::string UrlResponseHeadersToString(
    const mojom::UrlResponseInfo& mojom_url_response);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_URL_RESPONSE_STRING_UTIL_H_
