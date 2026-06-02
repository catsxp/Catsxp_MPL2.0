/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/browser/application_state/test/test_application_state_observer.h"

namespace catsxp_ads {

void TestApplicationStateObserver::OnBrowserDidBecomeActive() {
  ++foreground_count_;
}

void TestApplicationStateObserver::OnBrowserDidResignActive() {
  ++background_count_;
}

}  // namespace catsxp_ads
