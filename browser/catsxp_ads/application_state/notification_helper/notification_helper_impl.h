/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_H_
#define CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_H_

namespace catsxp_ads {

class NotificationHelperImpl {
 public:
  NotificationHelperImpl(const NotificationHelperImpl&) = delete;
  NotificationHelperImpl& operator=(const NotificationHelperImpl&) = delete;

  virtual ~NotificationHelperImpl();

  virtual void InitSystemNotifications();

  virtual bool CanShowNotifications();
  virtual bool CanShowSystemNotificationsWhileBrowserIsBackgrounded() const;

  virtual bool ShowOnboardingNotification();

 protected:
  friend class NotificationHelper;

  NotificationHelperImpl();
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_H_
