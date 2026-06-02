/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CATALOG_GEO_TARGET_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CATALOG_GEO_TARGET_INFO_H_

#include <string>
#include <vector>

namespace catsxp_ads {

struct CatalogGeoTargetInfo final {
  bool operator==(const CatalogGeoTargetInfo&) const = default;

  std::string code;
  std::string name;
};

using CatalogGeoTargetList = std::vector<CatalogGeoTargetInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CATALOG_GEO_TARGET_INFO_H_
