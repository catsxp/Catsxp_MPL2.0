/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/notification_ads/notification_ad_event_factory.h"

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/notification_ads/notification_ad_event_clicked.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/notification_ads/notification_ad_event_dismissed.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/notification_ads/notification_ad_event_served.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/notification_ads/notification_ad_event_timed_out.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/notification_ads/notification_ad_event_viewed.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/notification_ad/notification_ad_info.h"

namespace catsxp_ads {

std::unique_ptr<AdEventInterface<NotificationAdInfo>>
NotificationAdEventFactory::Build(
    mojom::NotificationAdEventType mojom_ad_event_type) {
  switch (mojom_ad_event_type) {
    case mojom::NotificationAdEventType::kServedImpression: {
      return std::make_unique<NotificationAdEventServed>();
    }

    case mojom::NotificationAdEventType::kViewedImpression: {
      return std::make_unique<NotificationAdEventViewed>();
    }

    case mojom::NotificationAdEventType::kClicked: {
      return std::make_unique<NotificationAdEventClicked>();
    }

    case mojom::NotificationAdEventType::kDismissed: {
      return std::make_unique<NotificationAdEventDismissed>();
    }

    case mojom::NotificationAdEventType::kTimedOut: {
      return std::make_unique<NotificationAdEventTimedOut>();
    }
  }
}

}  // namespace catsxp_ads
