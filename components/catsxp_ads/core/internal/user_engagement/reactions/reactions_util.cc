/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/user_engagement/reactions/reactions_util.h"

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"

namespace catsxp_ads {

mojom::ReactionInfoPtr CreateReaction(
    const AdHistoryItemInfo& ad_history_item) {
  mojom::ReactionInfoPtr mojom_reaction = mojom::ReactionInfo::New();

  mojom_reaction->mojom_ad_type = ad_history_item.type;
  mojom_reaction->creative_instance_id = ad_history_item.creative_instance_id;
  mojom_reaction->creative_set_id = ad_history_item.creative_set_id;
  mojom_reaction->advertiser_id = ad_history_item.advertiser_id;
  mojom_reaction->segment = ad_history_item.segment;

  return mojom_reaction;
}

}  // namespace catsxp_ads
