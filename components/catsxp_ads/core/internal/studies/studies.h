/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_STUDIES_STUDIES_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_STUDIES_STUDIES_H_

#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client_notifier_observer.h"

namespace catsxp_ads {

class AdsClient;

class Studies final : public AdsClientNotifierObserver {
 public:
  Studies();

  Studies(const Studies&) = delete;
  Studies& operator=(const Studies&) = delete;

  ~Studies() override;

 private:
  // AdsClientNotifierObserver:
  void OnNotifyDidInitializeAds() override;

  base::ScopedObservation<AdsClient, AdsClientNotifierObserver>
      ads_client_observation_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_STUDIES_STUDIES_H_
