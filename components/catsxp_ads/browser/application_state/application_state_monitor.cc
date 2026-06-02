/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/browser/application_state/application_state_monitor.h"

#include "catsxp/components/catsxp_ads/browser/application_state/application_state_observer.h"

namespace catsxp_ads {

ApplicationStateMonitor::ApplicationStateMonitor() = default;

ApplicationStateMonitor::~ApplicationStateMonitor() = default;

void ApplicationStateMonitor::AddObserver(
    ApplicationStateObserver* const observer) {
  observers_.AddObserver(observer);
}

void ApplicationStateMonitor::RemoveObserver(
    ApplicationStateObserver* const observer) {
  observers_.RemoveObserver(observer);
}

bool ApplicationStateMonitor::IsBrowserActive() const {
  return true;
}

void ApplicationStateMonitor::NotifyBrowserDidBecomeActive() {
  observers_.Notify(&ApplicationStateObserver::OnBrowserDidBecomeActive);
}

void ApplicationStateMonitor::NotifyBrowserDidResignActive() {
  observers_.Notify(&ApplicationStateObserver::OnBrowserDidResignActive);
}

}  // namespace catsxp_ads
