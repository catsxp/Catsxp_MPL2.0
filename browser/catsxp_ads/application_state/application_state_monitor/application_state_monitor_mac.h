/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_APPLICATION_STATE_MONITOR_APPLICATION_STATE_MONITOR_MAC_H_
#define CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_APPLICATION_STATE_MONITOR_APPLICATION_STATE_MONITOR_MAC_H_

#include <memory>

#include "catsxp/components/catsxp_ads/browser/application_state/application_state_monitor.h"

namespace catsxp_ads {

class ApplicationStateMonitorMac final : public ApplicationStateMonitor {
 public:
  ApplicationStateMonitorMac();

  ApplicationStateMonitorMac(const ApplicationStateMonitorMac&) = delete;
  ApplicationStateMonitorMac& operator=(const ApplicationStateMonitorMac&) =
      delete;

  ~ApplicationStateMonitorMac() override;

  // Called when the browser becomes active.
  void OnBrowserDidBecomeActive();

  // Called when the browser resigns active.
  void OnBrowserDidResignActive();

 private:
  // ApplicationStateMonitor:
  bool IsBrowserActive() const override;

  class Delegate;
  std::unique_ptr<Delegate> delegate_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_APPLICATION_STATE_MONITOR_APPLICATION_STATE_MONITOR_MAC_H_
