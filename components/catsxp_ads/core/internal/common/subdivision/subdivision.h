/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_SUBDIVISION_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_SUBDIVISION_H_

#include <memory>
#include <string>

#include "base/observer_list.h"
#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/subdivision_observer.h"
#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/url_request/subdivision_url_request_delegate.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client_notifier_observer.h"

namespace catsxp_ads {

class AdsClient;
class SubdivisionUrlRequest;

class Subdivision final : public AdsClientNotifierObserver,
                          public SubdivisionUrlRequestDelegate {
 public:
  Subdivision();

  Subdivision(const Subdivision&) = delete;
  Subdivision& operator=(const Subdivision&) = delete;

  ~Subdivision() override;

  void AddObserver(SubdivisionObserver* observer);
  void RemoveObserver(SubdivisionObserver* observer);

 private:
  void Initialize();

  void MaybeRequireSubdivision();
  void InitializeSubdivisionUrlRequest();
  void ShutdownSubdivisionUrlRequest();

  void MaybePeriodicallyFetchSubdivision();

  void NotifyDidUpdateSubdivision(const std::string& subdivision);

  // AdsClientNotifierObserver:
  void OnNotifyDidInitializeAds() override;
  void OnNotifyPrefDidChange(const std::string& path) override;

  // SubdivisionUrlRequestDelegate:
  void OnDidFetchSubdivision(const std::string& subdivision) override;

  base::ObserverList<SubdivisionObserver> observers_;

  base::ScopedObservation<AdsClient, AdsClientNotifierObserver>
      ads_client_observation_{this};

  std::unique_ptr<SubdivisionUrlRequest> subdivision_url_request_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_SUBDIVISION_H_
