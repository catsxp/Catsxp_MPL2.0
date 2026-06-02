/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_FACTORY_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_FACTORY_H_

#include <memory>

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_interface.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

struct NotificationAdInfo;

class NotificationAdEventFactory final {
 public:
  // This class contains only static methods.
  NotificationAdEventFactory() = delete;
  NotificationAdEventFactory(const NotificationAdEventFactory&) = delete;
  NotificationAdEventFactory& operator=(const NotificationAdEventFactory&) =
      delete;

  static std::unique_ptr<AdEventInterface<NotificationAdInfo>> Build(
      mojom::NotificationAdEventType mojom_ad_event_type);
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_FACTORY_H_
