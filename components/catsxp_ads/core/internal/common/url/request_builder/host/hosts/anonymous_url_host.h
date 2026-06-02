/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_HOSTS_ANONYMOUS_URL_HOST_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_HOSTS_ANONYMOUS_URL_HOST_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/hosts/url_host_interface.h"

namespace catsxp_ads {

class AnonymousUrlHost final : public UrlHostInterface {
 public:
  // UrlHostInterface:
  std::string Get() const override;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_HOSTS_ANONYMOUS_URL_HOST_H_
