/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/test/ads_observer_test_util.h"

#include <memory>
#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/ads_notifier_manager.h"
#include "catsxp/components/catsxp_ads/core/internal/test/ads_observer_mock.h"

namespace catsxp_ads::test {

AdsObserverMock* SetUpAdsObserverMock() {
  std::unique_ptr<AdsObserverMock> ads_observer_mock =
      std::make_unique<AdsObserverMock>();
  AdsObserverMock* const ads_observer_mock_ptr = ads_observer_mock.get();

  // `AdsNotifierManager` takes ownership of `ads_observer_mock`.
  AdsNotifierManager::GetInstance().AddObserver(std::move(ads_observer_mock));

  return ads_observer_mock_ptr;
}

}  // namespace catsxp_ads::test
