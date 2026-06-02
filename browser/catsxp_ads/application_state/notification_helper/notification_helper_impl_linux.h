/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_LINUX_H_
#define CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_LINUX_H_

#include "catsxp/browser/catsxp_ads/application_state/notification_helper/notification_helper_impl.h"

namespace catsxp_ads {

class NotificationHelperImplLinux final : public NotificationHelperImpl {
 public:
  NotificationHelperImplLinux(const NotificationHelperImplLinux&) = delete;
  NotificationHelperImplLinux& operator=(const NotificationHelperImplLinux&) =
      delete;

  ~NotificationHelperImplLinux() override;

 protected:
  friend class NotificationHelper;

  NotificationHelperImplLinux();

 private:
  // NotificationHelperImpl:
  bool CanShowNotifications() override;
  bool CanShowSystemNotificationsWhileBrowserIsBackgrounded() const override;

  bool ShowOnboardingNotification() override;
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_LINUX_H_
