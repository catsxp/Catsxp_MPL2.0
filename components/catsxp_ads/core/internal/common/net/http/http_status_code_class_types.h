/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_NET_HTTP_HTTP_STATUS_CODE_CLASS_TYPES_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_NET_HTTP_HTTP_STATUS_CODE_CLASS_TYPES_H_

namespace catsxp_ads {

enum class HttpStatusCodeClassType {
  kNonsensical = 0,
  kInformationalResponse = 1,  // 1xx
  kSuccess = 2,                // 2xx
  kRedirection = 3,            // 3xx
  kClientError = 4,            // 4xx
  kServerError = 5             // 5xx
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_NET_HTTP_HTTP_STATUS_CODE_CLASS_TYPES_H_
