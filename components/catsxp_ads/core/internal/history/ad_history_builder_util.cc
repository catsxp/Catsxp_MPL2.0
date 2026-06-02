/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/history/ad_history_builder_util.h"

#include "base/check.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/ad_info.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"

namespace catsxp_ads {

AdHistoryItemInfo BuildAdHistoryItem(
    const AdInfo& ad,
    mojom::ConfirmationType mojom_confirmation_type,
    const std::string& title,
    const std::string& description) {
  CHECK(ad.IsValid());

  AdHistoryItemInfo ad_history_item;

  ad_history_item.created_at = base::Time::Now();
  ad_history_item.type = ad.type;
  ad_history_item.confirmation_type = mojom_confirmation_type;
  ad_history_item.placement_id = ad.placement_id;
  ad_history_item.creative_instance_id = ad.creative_instance_id;
  ad_history_item.creative_set_id = ad.creative_set_id;
  ad_history_item.campaign_id = ad.campaign_id;
  ad_history_item.advertiser_id = ad.advertiser_id;
  ad_history_item.segment = ad.segment;
  ad_history_item.title = title;
  ad_history_item.description = description;
  ad_history_item.target_url = ad.target_url;

  return ad_history_item;
}

}  // namespace catsxp_ads
