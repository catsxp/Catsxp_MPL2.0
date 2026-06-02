/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_CLIENT_TEST_ADS_CLIENT_NOTIFIER_OBSERVER_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_CLIENT_TEST_ADS_CLIENT_NOTIFIER_OBSERVER_MOCK_H_

#include <cstdint>
#include <string>
#include <vector>

#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client_notifier_observer.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "ui/base/page_transition_types.h"

namespace catsxp_ads {

class AdsClientNotifierObserverMock : public AdsClientNotifierObserver {
 public:
  AdsClientNotifierObserverMock();

  AdsClientNotifierObserverMock(const AdsClientNotifierObserverMock&) = delete;
  AdsClientNotifierObserverMock& operator=(
      const AdsClientNotifierObserverMock&) = delete;

  ~AdsClientNotifierObserverMock() override;

  MOCK_METHOD(void, OnNotifyDidInitializeAds, ());

  MOCK_METHOD(void, OnNotifyPrefDidChange, (const std::string&));

  MOCK_METHOD(void,
              OnNotifyResourceComponentDidChange,
              (const std::string&, const std::string&));
  MOCK_METHOD(void,
              OnNotifyDidUnregisterResourceComponent,
              (const std::string&));

  MOCK_METHOD(void,
              OnNotifyRewardsWalletDidUpdate,
              (const std::string&, const std::string&));

  MOCK_METHOD(void,
              OnNotifyTabTextContentDidChange,
              (int32_t, const std::vector<GURL>&, const std::string&));
  MOCK_METHOD(void, OnNotifyTabDidStartPlayingMedia, (int32_t));
  MOCK_METHOD(void, OnNotifyTabDidStopPlayingMedia, (int32_t));
  MOCK_METHOD(void,
              OnNotifyTabDidChange,
              (int32_t, const std::vector<GURL>&, bool, bool, bool));
  MOCK_METHOD(void, OnNotifyTabDidLoad, (int32_t, int));
  MOCK_METHOD(void, OnNotifyDidCloseTab, (int32_t));

  MOCK_METHOD(void, OnNotifyUserGestureEventTriggered, (ui::PageTransition));

  MOCK_METHOD(void, OnNotifyUserDidBecomeIdle, ());
  MOCK_METHOD(void, OnNotifyUserDidBecomeActive, (base::TimeDelta, bool));

  MOCK_METHOD(void, OnNotifyBrowserDidEnterForeground, ());
  MOCK_METHOD(void, OnNotifyBrowserDidEnterBackground, ());
  MOCK_METHOD(void, OnNotifyBrowserDidBecomeActive, ());
  MOCK_METHOD(void, OnNotifyBrowserDidResignActive, ());

  MOCK_METHOD(void, OnNotifyDidSolveAdaptiveCaptcha, ());
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_CLIENT_TEST_ADS_CLIENT_NOTIFIER_OBSERVER_MOCK_H_
