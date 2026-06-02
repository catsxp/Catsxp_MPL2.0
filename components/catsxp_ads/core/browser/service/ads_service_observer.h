/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_SERVICE_ADS_SERVICE_OBSERVER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_SERVICE_ADS_SERVICE_OBSERVER_H_

#include "base/observer_list_types.h"

namespace catsxp_ads {

class AdsServiceObserver : public base::CheckedObserver {
 public:
  // Invoked when the ads service was ineligible to start.
  virtual void OnAdsServiceIneligibleToStart() {}

  // Invoked when the ads service has initialized.
  virtual void OnDidInitializeAdsService() {}

  // Invoked when the ads service has shutdown.
  virtual void OnDidShutdownAdsService() {}

  // Invoked when the ads service data has been cleared.
  virtual void OnDidClearAdsServiceData() {}
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_SERVICE_ADS_SERVICE_OBSERVER_H_
