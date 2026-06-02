/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_HANDLER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_HANDLER_H_

#include <string>

#include "base/check_op.h"
#include "base/functional/callback_forward.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/notification_ads/notification_ad_event_handler_delegate.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

using FireNotificationAdEventHandlerCallback = base::OnceCallback<void(
    bool success,
    const std::string& placement_id,
    mojom::NotificationAdEventType mojom_ad_event_type)>;

struct NotificationAdInfo;

class NotificationAdEventHandler final
    : public NotificationAdEventHandlerDelegate {
 public:
  NotificationAdEventHandler();

  NotificationAdEventHandler(const NotificationAdEventHandler&) = delete;
  NotificationAdEventHandler& operator=(const NotificationAdEventHandler&) =
      delete;

  ~NotificationAdEventHandler() override;

  void SetDelegate(NotificationAdEventHandlerDelegate* delegate) {
    CHECK_EQ(delegate_, nullptr);
    delegate_ = delegate;
  }

  void FireEvent(const std::string& placement_id,
                 mojom::NotificationAdEventType mojom_ad_event_type,
                 FireNotificationAdEventHandlerCallback callback);

 private:
  void FireEventCallback(const NotificationAdInfo& ad,
                         mojom::NotificationAdEventType mojom_ad_event_type,
                         FireNotificationAdEventHandlerCallback callback,
                         bool success) const;

  void SuccessfullyFiredEvent(
      const NotificationAdInfo& ad,
      mojom::NotificationAdEventType mojom_ad_event_type,
      FireNotificationAdEventHandlerCallback callback) const;
  void FailedToFireEvent(const std::string& placement_id,
                         mojom::NotificationAdEventType mojom_ad_event_type,
                         FireNotificationAdEventHandlerCallback callback) const;

  void NotifyWillFireNotificationAdClickedEvent(
      const NotificationAdInfo& ad) const;
  void NotifyDidFireNotificationAdEvent(
      const NotificationAdInfo& ad,
      mojom::NotificationAdEventType mojom_ad_event_type) const;
  void NotifyFailedToFireNotificationAdEvent(
      const std::string& placement_id,
      mojom::NotificationAdEventType mojom_ad_event_type) const;

  raw_ptr<NotificationAdEventHandlerDelegate> delegate_ =
      nullptr;  // Not owned.

  base::WeakPtrFactory<NotificationAdEventHandler> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_HANDLER_H_
