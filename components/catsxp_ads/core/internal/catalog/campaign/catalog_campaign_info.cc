/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/catalog/campaign/catalog_campaign_info.h"

#include <limits>

#include "base/numerics/ranges.h"

namespace catsxp_ads {

CatalogCampaignInfo::CatalogCampaignInfo() = default;

CatalogCampaignInfo::CatalogCampaignInfo(const CatalogCampaignInfo& other) =
    default;

CatalogCampaignInfo& CatalogCampaignInfo::operator=(
    const CatalogCampaignInfo& other) = default;

CatalogCampaignInfo::CatalogCampaignInfo(CatalogCampaignInfo&& other) noexcept =
    default;

CatalogCampaignInfo& CatalogCampaignInfo::operator=(
    CatalogCampaignInfo&& other) noexcept = default;

CatalogCampaignInfo::~CatalogCampaignInfo() = default;

bool CatalogCampaignInfo::operator==(const CatalogCampaignInfo& other) const {
  return id == other.id && priority == other.priority &&
         base::IsApproximatelyEqual(pass_through_rate, other.pass_through_rate,
                                    std::numeric_limits<double>::epsilon()) &&
         start_at == other.start_at && end_at == other.end_at &&
         daily_cap == other.daily_cap && advertiser_id == other.advertiser_id &&
         creative_sets == other.creative_sets && dayparts == other.dayparts &&
         geo_targets == other.geo_targets;
}

}  // namespace catsxp_ads
