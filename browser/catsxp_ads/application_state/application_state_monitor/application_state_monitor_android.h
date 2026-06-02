/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_APPLICATION_STATE_MONITOR_APPLICATION_STATE_MONITOR_ANDROID_H_
#define CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_APPLICATION_STATE_MONITOR_APPLICATION_STATE_MONITOR_ANDROID_H_

#include <memory>

#include "base/android/application_status_listener.h"
#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/browser/application_state/application_state_monitor.h"

namespace catsxp_ads {

class ApplicationStateMonitorAndroid final : public ApplicationStateMonitor {
 public:
  ApplicationStateMonitorAndroid();

  ApplicationStateMonitorAndroid(const ApplicationStateMonitorAndroid&) =
      delete;
  ApplicationStateMonitorAndroid& operator=(
      const ApplicationStateMonitorAndroid&) = delete;

  ~ApplicationStateMonitorAndroid() override;

 private:
  // ApplicationStatusListener:
  void OnApplicationStateChange(base::android::ApplicationState state);

  // ApplicationStateMonitor:
  bool IsBrowserActive() const override;

  std::unique_ptr<base::android::ApplicationStatusListener>
      application_status_listener_;

  base::android::ApplicationState application_state_;

  base::WeakPtrFactory<ApplicationStateMonitorAndroid> weak_ptr_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_APPLICATION_STATE_APPLICATION_STATE_MONITOR_APPLICATION_STATE_MONITOR_ANDROID_H_
