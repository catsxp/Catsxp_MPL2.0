/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_HOSTS_URL_HOST_INTERFACE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_HOSTS_URL_HOST_INTERFACE_H_

#include <string>

namespace catsxp_ads {

class UrlHostInterface {
 public:
  virtual ~UrlHostInterface() = default;

  virtual std::string Get() const = 0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_HOSTS_URL_HOST_INTERFACE_H_
