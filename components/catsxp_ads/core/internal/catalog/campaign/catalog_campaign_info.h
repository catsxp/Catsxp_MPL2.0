/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CATALOG_CAMPAIGN_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CATALOG_CAMPAIGN_INFO_H_

#include <string>
#include <vector>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/campaign/catalog_daypart_info.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/campaign/catalog_geo_target_info.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/campaign/creative_set/catalog_creative_set_info.h"

namespace catsxp_ads {

struct CatalogCampaignInfo final {
  CatalogCampaignInfo();

  CatalogCampaignInfo(const CatalogCampaignInfo&);
  CatalogCampaignInfo& operator=(const CatalogCampaignInfo&);

  CatalogCampaignInfo(CatalogCampaignInfo&&) noexcept;
  CatalogCampaignInfo& operator=(CatalogCampaignInfo&&) noexcept;

  ~CatalogCampaignInfo();

  bool operator==(const CatalogCampaignInfo&) const;

  std::string id;
  int priority = 0;
  double pass_through_rate = 0.0;
  base::Time start_at;
  base::Time end_at;
  int daily_cap = 0;
  std::string advertiser_id;
  CatalogCreativeSetList creative_sets;
  CatalogDaypartList dayparts;
  CatalogGeoTargetList geo_targets;
};

using CatalogCampaignList = std::vector<CatalogCampaignInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CATALOG_CAMPAIGN_INFO_H_
