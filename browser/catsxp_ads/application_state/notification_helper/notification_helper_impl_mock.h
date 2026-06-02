/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_MOCK_H_
#define CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_MOCK_H_

#include "catsxp/browser/catsxp_ads/application_state/notification_helper/notification_helper_impl.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class NotificationHelperImplMock : public NotificationHelperImpl {
 public:
  NotificationHelperImplMock();

  NotificationHelperImplMock(const NotificationHelperImplMock&) = delete;
  NotificationHelperImplMock& operator=(const NotificationHelperImplMock&) =
      delete;

  ~NotificationHelperImplMock() override;

  MOCK_METHOD(bool, CanShowNotifications, ());
  MOCK_METHOD(bool,
              CanShowSystemNotificationsWhileBrowserIsBackgrounded,
              (),
              (const));

  MOCK_METHOD(bool, ShowOnboardingNotification, ());
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_MOCK_H_
