/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_TEST_BROWSER_MANAGER_OBSERVER_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_TEST_BROWSER_MANAGER_OBSERVER_MOCK_H_

#include "catsxp/components/catsxp_ads/core/internal/application_state/browser_manager_observer.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class BrowserManagerObserverMock : public BrowserManagerObserver {
 public:
  BrowserManagerObserverMock();

  BrowserManagerObserverMock(const BrowserManagerObserverMock&) = delete;
  BrowserManagerObserverMock& operator=(const BrowserManagerObserverMock&) =
      delete;

  ~BrowserManagerObserverMock() override;

  MOCK_METHOD(void, OnBrowserDidBecomeActive, ());
  MOCK_METHOD(void, OnBrowserDidResignActive, ());

  MOCK_METHOD(void, OnBrowserDidEnterForeground, ());
  MOCK_METHOD(void, OnBrowserDidEnterBackground, ());
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_TEST_BROWSER_MANAGER_OBSERVER_MOCK_H_
