/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_APPLICATION_STATE_APPLICATION_STATE_MONITOR_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_APPLICATION_STATE_APPLICATION_STATE_MONITOR_H_

#include "base/observer_list.h"
#include "catsxp/components/catsxp_ads/browser/application_state/application_state_observer.h"

namespace catsxp_ads {
class ApplicationStateObserver;

// Notifies `ApplicationStateObserver` when the browser becomes active or
// inactive.
class ApplicationStateMonitor {
 public:
  ApplicationStateMonitor();

  ApplicationStateMonitor(const ApplicationStateMonitor&) = delete;
  ApplicationStateMonitor& operator=(const ApplicationStateMonitor&) = delete;

  virtual ~ApplicationStateMonitor();

  // Returns the singleton instance.
  static ApplicationStateMonitor* GetInstance();

  void AddObserver(ApplicationStateObserver* observer);
  void RemoveObserver(ApplicationStateObserver* observer);

  // Returns whether the browser is currently active.
  virtual bool IsBrowserActive() const;

  // Lifecycle
  virtual void Reset() {}

 protected:
  // Notifies observers that the browser became active.
  void NotifyBrowserDidBecomeActive();

  // Notifies observers that the browser resigned active.
  void NotifyBrowserDidResignActive();

 private:
  base::ObserverList<ApplicationStateObserver> observers_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_APPLICATION_STATE_APPLICATION_STATE_MONITOR_H_
