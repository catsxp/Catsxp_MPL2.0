/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_HANDLER_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_HANDLER_DELEGATE_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

struct NotificationAdInfo;

class NotificationAdEventHandlerDelegate {
 public:
  // Invoked when the notification `ad` is served.
  virtual void OnDidFireNotificationAdServedEvent(
      const NotificationAdInfo& ad) {}

  // Invoked when the notification `ad` is viewed.
  virtual void OnDidFireNotificationAdViewedEvent(
      const NotificationAdInfo& ad) {}

  // Invoked before the click ad event for `ad` is recorded.
  virtual void OnWillFireNotificationAdClickedEvent(
      const NotificationAdInfo& ad) {}

  // Invoked when the notification `ad` is clicked.
  virtual void OnDidFireNotificationAdClickedEvent(
      const NotificationAdInfo& ad) {}

  // Invoked when the notification `ad` is dismissed.
  virtual void OnDidFireNotificationAdDismissedEvent(
      const NotificationAdInfo& ad) {}

  // Invoked when the notification `ad` times out.
  virtual void OnDidFireNotificationAdTimedOutEvent(
      const NotificationAdInfo& ad) {}

  // Invoked when the notification ad event fails for `placement_id` and
  // `mojom_ad_event_type`.
  virtual void OnFailedToFireNotificationAdEvent(
      const std::string& placement_id,
      mojom::NotificationAdEventType mojom_ad_event_type) {}

 protected:
  virtual ~NotificationAdEventHandlerDelegate() = default;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_HANDLER_DELEGATE_H_
