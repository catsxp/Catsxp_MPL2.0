/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_H_
#define CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_H_

#include <memory>

#include "base/memory/weak_ptr.h"

class Profile;

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace catsxp_ads {

class NotificationHelperImpl;

class NotificationHelper final {
 public:
  NotificationHelper(const NotificationHelper&) = delete;
  NotificationHelper& operator=(const NotificationHelper&) = delete;

  static NotificationHelper* GetInstance();

  void MaybeInitForProfile(Profile* profile);

  bool CanShowNotifications();
  bool CanShowSystemNotificationsWhileBrowserIsBackgrounded() const;

  bool ShowOnboardingNotification();

  bool DoesSupportSystemNotifications() const;

 private:
  friend base::NoDestructor<NotificationHelper>;

  NotificationHelper();

  ~NotificationHelper();

  void OnSystemNotificationPlatformBridgeReady(bool success);

  bool is_initialized_ = false;

  bool does_support_system_notifications_ = true;

  std::unique_ptr<NotificationHelperImpl> impl_;

  base::WeakPtrFactory<NotificationHelper> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_H_
