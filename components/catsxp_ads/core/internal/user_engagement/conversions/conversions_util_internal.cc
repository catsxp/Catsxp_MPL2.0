/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversions_util_internal.h"

#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

bool CanConvertAdEvent(const AdEventInfo& ad_event) {
  if (UserHasJoinedCatsxpRewards()) {
    // For Rewards users, allow both view-through and click-through conversions.
    return ad_event.confirmation_type ==
               mojom::ConfirmationType::kViewedImpression ||
           ad_event.confirmation_type == mojom::ConfirmationType::kClicked;
  }

  // Otherwise, only allow click-through conversions.
  return ad_event.confirmation_type == mojom::ConfirmationType::kClicked;
}

}  // namespace catsxp_ads
