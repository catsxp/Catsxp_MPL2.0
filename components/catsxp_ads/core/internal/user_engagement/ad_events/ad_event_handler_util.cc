/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_handler_util.h"

#include <algorithm>

#include "base/check.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/ad_info.h"

namespace catsxp_ads {

bool HasFiredAdEvent(const AdInfo& ad,
                     const AdEventList& ad_events,
                     mojom::ConfirmationType mojom_confirmation_type) {
  const auto iter = std::ranges::find_if(
      ad_events, [&ad, mojom_confirmation_type](const AdEventInfo& ad_event) {
        return ad_event.placement_id == ad.placement_id &&
               ad_event.confirmation_type == mojom_confirmation_type;
      });

  return iter != ad_events.cend();
}

bool HasFiredAdEventWithinTimeWindow(
    const AdInfo& ad,
    const AdEventList& ad_events,
    mojom::ConfirmationType mojom_confirmation_type,
    base::TimeDelta time_window) {
  const auto iter = std::ranges::find_if(
      ad_events,
      [&ad, mojom_confirmation_type, time_window](const AdEventInfo& ad_event) {
        CHECK(ad_event.created_at);

        return ad_event.placement_id == ad.placement_id &&
               ad_event.confirmation_type == mojom_confirmation_type &&
               (time_window.is_zero() ||
                base::Time::Now() - *ad_event.created_at <= time_window);
      });

  return iter != ad_events.cend();
}

}  // namespace catsxp_ads
