/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_URL_REQUEST_BUILDER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_URL_REQUEST_BUILDER_H_

#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/url_request_builder_interface.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

class CatalogUrlRequestBuilder final : public UrlRequestBuilderInterface {
 public:
  // UrlRequestBuilderInterface:
  mojom::UrlRequestInfoPtr Build() override;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_URL_REQUEST_BUILDER_H_
