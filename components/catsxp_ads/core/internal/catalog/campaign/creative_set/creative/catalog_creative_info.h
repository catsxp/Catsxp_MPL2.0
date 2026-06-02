/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_CATALOG_CREATIVE_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_CATALOG_CREATIVE_INFO_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/catalog/campaign/creative_set/creative/catalog_type_info.h"

namespace catsxp_ads {

struct CatalogCreativeInfo {
  bool operator==(const CatalogCreativeInfo&) const = default;

  std::string instance_id;
  CatalogTypeInfo type;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_CATALOG_CREATIVE_INFO_H_
