/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_NET_HTTP_HTTP_STATUS_CODE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_NET_HTTP_HTTP_STATUS_CODE_UTIL_H_

#include <optional>
#include <string>

#include "catsxp/components/catsxp_ads/core/internal/common/net/http/http_status_code_class_types.h"

namespace catsxp_ads {

HttpStatusCodeClassType HttpStatusCodeClass(int http_status_code);

bool IsSuccessfulHttpStatusCode(int http_status_code);

std::optional<std::string> HttpStatusCodeToString(int http_status_code);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_NET_HTTP_HTTP_STATUS_CODE_UTIL_H_
