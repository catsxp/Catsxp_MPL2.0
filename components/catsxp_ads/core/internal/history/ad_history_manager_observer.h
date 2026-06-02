/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_MANAGER_OBSERVER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_MANAGER_OBSERVER_H_

#include "base/observer_list_types.h"

namespace catsxp_ads {

struct AdHistoryItemInfo;

class AdHistoryManagerObserver : public base::CheckedObserver {
 public:
  // Invoked when ad history is added.
  virtual void OnDidAddAdHistoryItem(const AdHistoryItemInfo& ad_history_item) {
  }
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_MANAGER_OBSERVER_H_
