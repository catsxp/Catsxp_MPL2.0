/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_builder.h"

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

namespace {
constexpr char kSegment[] = "keyword";
}  // namespace

SearchResultAdInfo FromMojomBuildSearchResultAd(
    const mojom::CreativeSearchResultAdInfoPtr& mojom_creative_ad) {
  CHECK(mojom_creative_ad);

  SearchResultAdInfo ad;

  ad.type = mojom::AdType::kSearchResultAd;
  ad.placement_id = mojom_creative_ad->placement_id;
  ad.creative_instance_id = mojom_creative_ad->creative_instance_id;
  ad.creative_set_id = mojom_creative_ad->creative_set_id;
  ad.campaign_id = mojom_creative_ad->campaign_id;
  ad.advertiser_id = mojom_creative_ad->advertiser_id;
  ad.segment = kSegment;
  ad.target_url = mojom_creative_ad->target_url;
  ad.headline_text = mojom_creative_ad->headline_text;
  ad.description = mojom_creative_ad->description;

  return ad;
}

}  // namespace catsxp_ads
