/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TABS_TEST_TAB_MANAGER_OBSERVER_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TABS_TEST_TAB_MANAGER_OBSERVER_MOCK_H_

#include <cstdint>
#include <string>

#include "base/containers/span.h"
#include "catsxp/components/catsxp_ads/core/internal/tabs/tab_manager_observer.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class TabManagerObserverMock : public TabManagerObserver {
 public:
  TabManagerObserverMock();

  TabManagerObserverMock(const TabManagerObserverMock&) = delete;
  TabManagerObserverMock& operator=(const TabManagerObserverMock&) = delete;

  ~TabManagerObserverMock() override;

  MOCK_METHOD(void, OnDidOpenNewTab, (const TabInfo&));

  MOCK_METHOD(void, OnTabDidLoad, (const TabInfo&, int));

  MOCK_METHOD(void, OnTabDidChangeFocus, (int32_t));

  MOCK_METHOD(void, OnTabDidChange, (const TabInfo&));

  MOCK_METHOD(void,
              OnTextContentDidChange,
              (int32_t, base::span<const GURL>, const std::string&));

  MOCK_METHOD(void, OnDidCloseTab, (int32_t));

  MOCK_METHOD(void, OnTabDidStartPlayingMedia, (int32_t));
  MOCK_METHOD(void, OnTabDidStopPlayingMedia, (int32_t));
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TABS_TEST_TAB_MANAGER_OBSERVER_MOCK_H_
