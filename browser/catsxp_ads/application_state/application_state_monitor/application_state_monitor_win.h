/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_APPLICATION_STATE_MONITOR_APPLICATION_STATE_MONITOR_WIN_H_
#define CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_APPLICATION_STATE_MONITOR_APPLICATION_STATE_MONITOR_WIN_H_

#include "base/callback_list.h"
#include "base/win/windows_types.h"
#include "catsxp/components/catsxp_ads/browser/application_state/application_state_monitor.h"

namespace catsxp_ads {

class ApplicationStateMonitorWin final : public ApplicationStateMonitor {
 public:
  ApplicationStateMonitorWin();

  ApplicationStateMonitorWin(const ApplicationStateMonitorWin&) = delete;
  ApplicationStateMonitorWin& operator=(const ApplicationStateMonitorWin&) =
      delete;

  ~ApplicationStateMonitorWin() override;

 private:
  void OnWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

  // ApplicationStateMonitor:
  bool IsBrowserActive() const override;

  base::CallbackListSubscription singleton_hwnd_subscription_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_APPLICATION_STATE_MONITOR_APPLICATION_STATE_MONITOR_WIN_H_
