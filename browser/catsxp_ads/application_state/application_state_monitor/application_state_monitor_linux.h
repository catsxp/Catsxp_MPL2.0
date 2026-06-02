/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_APPLICATION_STATE_MONITOR_APPLICATION_STATE_MONITOR_LINUX_H_
#define CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_APPLICATION_STATE_MONITOR_APPLICATION_STATE_MONITOR_LINUX_H_

#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/browser/application_state/application_state_monitor.h"
#include "chrome/browser/ui/browser_window/public/browser_collection_observer.h"

class BrowserCollection;

namespace catsxp_ads {

class ApplicationStateMonitorLinux final : public ApplicationStateMonitor,
                                           public BrowserCollectionObserver {
 public:
  ApplicationStateMonitorLinux();

  ApplicationStateMonitorLinux(const ApplicationStateMonitorLinux&) = delete;
  ApplicationStateMonitorLinux& operator=(const ApplicationStateMonitorLinux&) =
      delete;

  ~ApplicationStateMonitorLinux() override;

  void Reset() override;

 private:
  // BrowserCollectionObserver:
  void OnBrowserActivated(BrowserWindowInterface* browser) override;
  void OnBrowserDeactivated(BrowserWindowInterface* browser) override;

  // ApplicationStateMonitor:
  bool IsBrowserActive() const override;

  base::ScopedObservation<BrowserCollection, BrowserCollectionObserver>
      browser_collection_observation_{this};
  base::WeakPtrFactory<ApplicationStateMonitorLinux> weak_ptr_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_APPLICATION_STATE_MONITOR_APPLICATION_STATE_MONITOR_LINUX_H_
