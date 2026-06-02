/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_URL_HOST_TYPES_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_URL_HOST_TYPES_H_

namespace catsxp_ads {

enum class UrlHostType {
  // Use for requests that must not include the wallet ID or allow Catsxp to
  // link the request to a wallet in any other way.
  kAnonymous = 0,

  // Use for search requests that must not include the wallet ID or allow Catsxp
  // to link the request to a wallet in any other way.
  kAnonymousSearch,

  // Only used by the /v#/getstate endpoint.
  kGeo,

  // Use for requests that include the wallet ID and therefore fully identify
  // the user.
  kNonAnonymous,

  // Use for requests that are not user-specific and do not process personal
  // data.
  kStatic
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_URL_HOST_TYPES_H_
