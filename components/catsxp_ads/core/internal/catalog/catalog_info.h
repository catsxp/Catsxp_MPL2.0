/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_INFO_H_

#include <string>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/campaign/catalog_campaign_info.h"

namespace catsxp_ads {

struct CatalogInfo final {
  CatalogInfo();

  CatalogInfo(const CatalogInfo&);
  CatalogInfo& operator=(const CatalogInfo&);

  CatalogInfo(CatalogInfo&&) noexcept;
  CatalogInfo& operator=(CatalogInfo&&) noexcept;

  ~CatalogInfo();

  bool operator==(const CatalogInfo&) const = default;

  std::string id;
  int version = 0;
  base::TimeDelta ping;
  CatalogCampaignList campaigns;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_INFO_H_
