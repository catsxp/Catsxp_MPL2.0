/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/reactions/test/reactions_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads::test {

mojom::ReactionInfoPtr BuildReaction(mojom::AdType mojom_ad_type) {
  mojom::ReactionInfoPtr mojom_reaction = mojom::ReactionInfo::New();

  mojom_reaction->mojom_ad_type = mojom_ad_type;
  mojom_reaction->creative_instance_id = kCreativeInstanceId;
  mojom_reaction->creative_set_id = kCreativeSetId;
  mojom_reaction->campaign_id = kCampaignId;
  mojom_reaction->advertiser_id = kAdvertiserId;
  mojom_reaction->segment = kSegment;

  return mojom_reaction;
}

}  // namespace catsxp_ads::test
