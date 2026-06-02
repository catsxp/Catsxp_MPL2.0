/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversions_util.h"

#include <utility>

#include "base/notreached.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversions_util_internal.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

bool IsAllowedToConvertAdEvent(const AdEventInfo& ad_event) {
  if (!CanConvertAdEvent(ad_event)) {
    return false;
  }

  switch (ad_event.type) {
    case mojom::AdType::kNewTabPageAd: {
      // Only if:
      // - The user has opted into new tab page ads and has joined Catsxp
      //   Rewards.
      return UserHasOptedInToNewTabPageAds() && UserHasJoinedCatsxpRewards();
    }

    case mojom::AdType::kNotificationAd: {
      // Only if:
      // - The user has opted into notification ads. Users cannot opt into
      //   notification ads without joining Catsxp Rewards.
      return UserHasOptedInToNotificationAds();
    }

    case mojom::AdType::kSearchResultAd: {
      // Only if:
      // - The user has opted into search result ads.
      return UserHasOptedInToSearchResultAds();
    }

    case mojom::AdType::kUndefined: {
      break;
    }
  }

  NOTREACHED() << "Unexpected value for mojom::AdType: "
               << std::to_underlying(ad_event.type);
}

bool DidAdEventOccurWithinObservationWindow(
    const AdEventInfo& ad_event,
    base::TimeDelta observation_window) {
  return ad_event.created_at >= base::Time::Now() - observation_window;
}

}  // namespace catsxp_ads
