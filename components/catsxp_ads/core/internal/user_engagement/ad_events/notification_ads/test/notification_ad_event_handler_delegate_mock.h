/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_TEST_NOTIFICATION_AD_EVENT_HANDLER_DELEGATE_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_TEST_NOTIFICATION_AD_EVENT_HANDLER_DELEGATE_MOCK_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/notification_ads/notification_ad_event_handler_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class NotificationAdEventHandlerDelegateMock
    : public NotificationAdEventHandlerDelegate {
 public:
  NotificationAdEventHandlerDelegateMock();

  NotificationAdEventHandlerDelegateMock(
      const NotificationAdEventHandlerDelegateMock&) = delete;
  NotificationAdEventHandlerDelegateMock& operator=(
      const NotificationAdEventHandlerDelegateMock&) = delete;

  ~NotificationAdEventHandlerDelegateMock() override;

  MOCK_METHOD(void,
              OnDidFireNotificationAdServedEvent,
              (const NotificationAdInfo&));
  MOCK_METHOD(void,
              OnDidFireNotificationAdViewedEvent,
              (const NotificationAdInfo&));
  MOCK_METHOD(void,
              OnWillFireNotificationAdClickedEvent,
              (const NotificationAdInfo&));
  MOCK_METHOD(void,
              OnDidFireNotificationAdClickedEvent,
              (const NotificationAdInfo&));
  MOCK_METHOD(void,
              OnDidFireNotificationAdDismissedEvent,
              (const NotificationAdInfo&));
  MOCK_METHOD(void,
              OnDidFireNotificationAdTimedOutEvent,
              (const NotificationAdInfo&));
  MOCK_METHOD(void,
              OnFailedToFireNotificationAdEvent,
              (const std::string&, mojom::NotificationAdEventType));
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_TEST_NOTIFICATION_AD_EVENT_HANDLER_DELEGATE_MOCK_H_
