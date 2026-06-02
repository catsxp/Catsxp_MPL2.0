/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_VIEWED_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_VIEWED_H_

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_interface.h"

namespace catsxp_ads {

struct NotificationAdInfo;

class NotificationAdEventViewed final
    : public AdEventInterface<NotificationAdInfo> {
 public:
  // AdEventInterface:
  void FireEvent(const NotificationAdInfo& ad,
                 ResultCallback callback) override;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_VIEWED_H_
