/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/new_tab_page_ad_builder.h"

#include "base/uuid.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_info.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_info.h"

namespace catsxp_ads {

NewTabPageAdInfo BuildNewTabPageAd(
    const CreativeNewTabPageAdInfo& creative_ad) {
  const std::string placement_id =
      base::Uuid::GenerateRandomV4().AsLowercaseString();
  return BuildNewTabPageAd(placement_id, creative_ad);
}

NewTabPageAdInfo BuildNewTabPageAd(
    const std::string& placement_id,
    const CreativeNewTabPageAdInfo& creative_ad) {
  NewTabPageAdInfo ad;

  ad.type = mojom::AdType::kNewTabPageAd;
  ad.placement_id = placement_id;
  ad.creative_instance_id = creative_ad.creative_instance_id;
  ad.creative_set_id = creative_ad.creative_set_id;
  ad.campaign_id = creative_ad.campaign_id;
  ad.advertiser_id = creative_ad.advertiser_id;
  ad.segment = creative_ad.segment;
  ad.company_name = creative_ad.company_name;
  ad.alt = creative_ad.alt;
  ad.target_url = creative_ad.target_url;

  return ad;
}

}  // namespace catsxp_ads
