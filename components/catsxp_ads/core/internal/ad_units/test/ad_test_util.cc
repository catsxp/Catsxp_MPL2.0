/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_util.h"

#include "base/uuid.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/ad_info.h"
#include "url/gurl.h"

namespace catsxp_ads::test {

std::string RandomUuidOr(bool should_generate_random_uuid,
                         const std::string& or_uuid) {
  return should_generate_random_uuid
             ? base::Uuid::GenerateRandomV4().AsLowercaseString()
             : or_uuid;
}

AdInfo BuildAd(mojom::AdType mojom_ad_type, bool use_random_uuids) {
  AdInfo ad;

  ad.type = mojom_ad_type;
  ad.placement_id = RandomUuidOr(use_random_uuids, kPlacementId);
  ad.creative_instance_id = RandomUuidOr(use_random_uuids, kCreativeInstanceId);
  ad.creative_set_id = RandomUuidOr(use_random_uuids, kCreativeSetId);
  ad.campaign_id = RandomUuidOr(use_random_uuids, kCampaignId);
  ad.advertiser_id = RandomUuidOr(use_random_uuids, kAdvertiserId);
  ad.segment = kSegment;
  ad.target_url = GURL(kTargetUrl);

  return ad;
}

}  // namespace catsxp_ads::test
