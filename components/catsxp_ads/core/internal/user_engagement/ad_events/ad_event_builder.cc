/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/ad_info.h"

namespace catsxp_ads {

AdEventInfo BuildAdEvent(const AdInfo& ad,
                         mojom::ConfirmationType mojom_confirmation_type,
                         base::Time created_at) {
  AdEventInfo ad_event;

  ad_event.type = ad.type;
  ad_event.confirmation_type = mojom_confirmation_type;
  ad_event.placement_id = ad.placement_id;
  ad_event.campaign_id = ad.campaign_id;
  ad_event.creative_set_id = ad.creative_set_id;
  ad_event.creative_instance_id = ad.creative_instance_id;
  ad_event.advertiser_id = ad.advertiser_id;
  ad_event.segment = ad.segment;
  ad_event.target_url = ad.target_url;
  ad_event.created_at = created_at;

  return ad_event;
}

AdEventInfo RebuildAdEvent(const AdEventInfo& ad_event,
                           mojom::ConfirmationType mojom_confirmation_type,
                           base::Time created_at) {
  AdEventInfo mutable_ad_event(ad_event);

  mutable_ad_event.confirmation_type = mojom_confirmation_type;
  mutable_ad_event.created_at = created_at;

  return mutable_ad_event;
}

}  // namespace catsxp_ads
