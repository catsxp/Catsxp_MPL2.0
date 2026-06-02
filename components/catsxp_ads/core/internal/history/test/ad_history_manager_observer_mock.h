/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_TEST_AD_HISTORY_MANAGER_OBSERVER_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_TEST_AD_HISTORY_MANAGER_OBSERVER_MOCK_H_

#include "catsxp/components/catsxp_ads/core/internal/history/ad_history_manager_observer.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

struct AdHistoryItemInfo;

class AdHistoryManagerObserverMock : public AdHistoryManagerObserver {
 public:
  AdHistoryManagerObserverMock();

  AdHistoryManagerObserverMock(const AdHistoryManagerObserverMock&) = delete;
  AdHistoryManagerObserverMock& operator=(const AdHistoryManagerObserverMock&) =
      delete;

  ~AdHistoryManagerObserverMock() override;

  MOCK_METHOD(void, OnDidAddAdHistoryItem, (const AdHistoryItemInfo&));
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_TEST_AD_HISTORY_MANAGER_OBSERVER_MOCK_H_
