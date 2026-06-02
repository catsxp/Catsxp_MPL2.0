/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/search_result_ads/test/creative_search_result_ad_test_util.h"

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "url/gurl.h"

namespace catsxp_ads::test {

namespace {

constexpr char kConversionUrlPattern[] = "https://catsxp.com/*";
constexpr base::TimeDelta kConversionObservationWindow = base::Days(3);

}  // namespace

mojom::CreativeSearchResultAdInfoPtr BuildCreativeSearchResultAd(
    bool use_random_uuids) {
  mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      mojom::CreativeSearchResultAdInfo::New();

  mojom_creative_ad->placement_id =
      RandomUuidOr(use_random_uuids, kPlacementId);
  mojom_creative_ad->creative_instance_id =
      RandomUuidOr(use_random_uuids, kCreativeInstanceId);
  mojom_creative_ad->creative_set_id =
      RandomUuidOr(use_random_uuids, kCreativeSetId);
  mojom_creative_ad->campaign_id = RandomUuidOr(use_random_uuids, kCampaignId);
  mojom_creative_ad->advertiser_id =
      RandomUuidOr(use_random_uuids, kAdvertiserId);
  mojom_creative_ad->target_url = GURL(kTargetUrl);
  mojom_creative_ad->headline_text = kTitle;
  mojom_creative_ad->description = kDescription;
  mojom_creative_ad->value = kValue;

  return mojom_creative_ad;
}

mojom::CreativeSearchResultAdInfoPtr BuildCreativeSearchResultAdWithConversion(
    bool use_random_uuids) {
  mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      BuildCreativeSearchResultAd(use_random_uuids);
  CHECK(mojom_creative_ad);

  mojom_creative_ad->creative_set_conversion =
      mojom::CreativeSetConversionInfo::New();
  mojom_creative_ad->creative_set_conversion->url_pattern =
      kConversionUrlPattern;
  mojom_creative_ad->creative_set_conversion->observation_window =
      kConversionObservationWindow;

  return mojom_creative_ad;
}

}  // namespace catsxp_ads::test
