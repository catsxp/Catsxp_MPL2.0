/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CATALOG_OS_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CATALOG_OS_INFO_H_

#include <string>
#include <vector>

namespace catsxp_ads {

struct CatalogOsInfo final {
  bool operator==(const CatalogOsInfo&) const = default;

  std::string code;
  std::string name;
};

using CatalogOsList = std::vector<CatalogOsInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CATALOG_OS_INFO_H_
