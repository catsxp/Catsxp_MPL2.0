/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_ANDROID_H_
#define CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_ANDROID_H_

#include "catsxp/browser/catsxp_ads/application_state/notification_helper/notification_helper_impl.h"

namespace catsxp_ads {

class NotificationHelperImplAndroid final : public NotificationHelperImpl {
 public:
  NotificationHelperImplAndroid(const NotificationHelperImplAndroid&) = delete;
  NotificationHelperImplAndroid& operator=(
      const NotificationHelperImplAndroid&) = delete;

  ~NotificationHelperImplAndroid() override;

 protected:
  friend class NotificationHelper;

  NotificationHelperImplAndroid();

 private:
  // NotificationHelperLinux:
  bool CanShowNotifications() override;
  bool CanShowSystemNotificationsWhileBrowserIsBackgrounded() const override;

  bool ShowOnboardingNotification() override;
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_ANDROID_H_
