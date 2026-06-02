/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_URL_HOST_FACTORY_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_URL_HOST_FACTORY_H_

#include <memory>

#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/hosts/url_host_interface.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/url_host_types.h"

namespace catsxp_ads {

class UrlHostFactory final {
 public:
  // This class contains only static methods.
  UrlHostFactory() = delete;
  UrlHostFactory(const UrlHostFactory&) = delete;
  UrlHostFactory& operator=(const UrlHostFactory&) = delete;

  static std::unique_ptr<UrlHostInterface> Build(UrlHostType type);
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_URL_HOST_FACTORY_H_
