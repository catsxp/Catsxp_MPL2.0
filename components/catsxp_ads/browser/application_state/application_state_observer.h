/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_APPLICATION_STATE_APPLICATION_STATE_OBSERVER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_APPLICATION_STATE_APPLICATION_STATE_OBSERVER_H_

#include "base/observer_list_types.h"

namespace catsxp_ads {

class ApplicationStateObserver : public base::CheckedObserver {
 public:
  ~ApplicationStateObserver() override = default;

  // Called when the browser becomes active.
  virtual void OnBrowserDidBecomeActive() = 0;

  // Called when the browser resigns active.
  virtual void OnBrowserDidResignActive() = 0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_APPLICATION_STATE_APPLICATION_STATE_OBSERVER_H_
