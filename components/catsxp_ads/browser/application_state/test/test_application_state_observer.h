/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_APPLICATION_STATE_TEST_TEST_APPLICATION_STATE_OBSERVER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_APPLICATION_STATE_TEST_TEST_APPLICATION_STATE_OBSERVER_H_

#include <cstddef>

#include "catsxp/components/catsxp_ads/browser/application_state/application_state_observer.h"

namespace catsxp_ads {

// Test implementation of `ApplicationStateObserver` that counts callback
// invocations.
class TestApplicationStateObserver : public ApplicationStateObserver {
 public:
  void OnBrowserDidBecomeActive() override;
  void OnBrowserDidResignActive() override;

  size_t foreground_count() const { return foreground_count_; }
  size_t background_count() const { return background_count_; }

 private:
  size_t foreground_count_ = 0;
  size_t background_count_ = 0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_APPLICATION_STATE_TEST_TEST_APPLICATION_STATE_OBSERVER_H_
