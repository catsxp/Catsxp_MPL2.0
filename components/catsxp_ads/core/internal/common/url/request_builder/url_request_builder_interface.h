/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_URL_REQUEST_BUILDER_INTERFACE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_URL_REQUEST_BUILDER_INTERFACE_H_

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

class UrlRequestBuilderInterface {
 public:
  virtual mojom::UrlRequestInfoPtr Build() = 0;

 protected:
  virtual ~UrlRequestBuilderInterface() = default;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_URL_REQUEST_BUILDER_INTERFACE_H_
