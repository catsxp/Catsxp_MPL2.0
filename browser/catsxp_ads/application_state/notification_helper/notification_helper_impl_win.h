/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_WIN_H_
#define CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_WIN_H_

#include <windows.ui.notifications.h>
#include <wrl/event.h>

#include "base/memory/weak_ptr.h"
#include "catsxp/browser/catsxp_ads/application_state/notification_helper/notification_helper_impl.h"

namespace catsxp_ads {

class NotificationHelperImplWin final : public NotificationHelperImpl {
 public:
  NotificationHelperImplWin(const NotificationHelperImplWin&) = delete;
  NotificationHelperImplWin& operator=(const NotificationHelperImplWin&) =
      delete;

  ~NotificationHelperImplWin() override;

  // NotificationHelperImpl:
  void InitSystemNotifications() override;
  bool CanShowNotifications() override;
  bool CanShowSystemNotificationsWhileBrowserIsBackgrounded() const override;
  bool ShowOnboardingNotification() override;

 protected:
  friend class NotificationHelper;
  NotificationHelperImplWin();

  void InitSystemNotificationsCallback(
      Microsoft::WRL::ComPtr<ABI::Windows::UI::Notifications::IToastNotifier>
          toast_notifier);

  bool IsFocusAssistEnabled() const;

  bool IsNotificationsEnabled();

  Microsoft::WRL::ComPtr<ABI::Windows::UI::Notifications::IToastNotifier>
      toast_notifier_;
  base::WeakPtrFactory<NotificationHelperImplWin> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_WIN_H_
