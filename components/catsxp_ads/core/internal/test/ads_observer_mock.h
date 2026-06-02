/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TEST_ADS_OBSERVER_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TEST_ADS_OBSERVER_MOCK_H_

#include "catsxp/components/catsxp_ads/core/public/ads_observer.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class AdsObserverMock : public AdsObserver {
 public:
  AdsObserverMock();

  AdsObserverMock(const AdsObserverMock&) = delete;
  AdsObserverMock& operator=(const AdsObserverMock&) = delete;

  ~AdsObserverMock() override;

  MOCK_METHOD(void, OnAdRewardsDidChange, ());

  MOCK_METHOD(void, OnBrowserUpgradeRequiredToServeAds, ());

  MOCK_METHOD(void, OnIneligibleWalletToServeAds, ());

  MOCK_METHOD(void, OnRemindUser, (mojom::ReminderType));
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TEST_ADS_OBSERVER_MOCK_H_
