/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_BROWSER_MANAGER_OBSERVER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_BROWSER_MANAGER_OBSERVER_H_

#include "base/observer_list_types.h"

namespace catsxp_ads {

class BrowserManagerObserver : public base::CheckedObserver {
 public:
  // Invoked when the browser becomes active.
  virtual void OnBrowserDidBecomeActive() {}

  // Invoked when the browser becomes inactive.
  virtual void OnBrowserDidResignActive() {}

  // Invoked when the browser enters the foreground.
  virtual void OnBrowserDidEnterForeground() {}

  // Invoked when the browser enters the background.
  virtual void OnBrowserDidEnterBackground() {}
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_BROWSER_MANAGER_OBSERVER_H_
