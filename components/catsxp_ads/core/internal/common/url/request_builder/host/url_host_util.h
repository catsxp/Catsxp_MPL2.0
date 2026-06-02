/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_URL_HOST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_URL_HOST_UTIL_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/url_host_types.h"

namespace catsxp_ads {

// Returns the URL host for the given `type`. See `UrlHostType` for
// usage guidance on each value.
std::string GetUrlHost(UrlHostType type);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_URL_HOST_UTIL_H_
