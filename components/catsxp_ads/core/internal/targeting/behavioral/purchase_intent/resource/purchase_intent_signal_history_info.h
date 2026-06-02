/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_SIGNAL_HISTORY_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_SIGNAL_HISTORY_INFO_H_

#include <map>
#include <string>
#include <vector>

#include "base/time/time.h"

namespace catsxp_ads {

struct PurchaseIntentSignalHistoryInfo final {
  PurchaseIntentSignalHistoryInfo(base::Time at, int weight);

  bool operator==(const PurchaseIntentSignalHistoryInfo&) const = default;

  base::Time at;
  int weight = 0;
};

using PurchaseIntentSignalHistoryList =
    std::vector<PurchaseIntentSignalHistoryInfo>;
using PurchaseIntentSignalHistoryMap =
    std::map</*segment*/ std::string, PurchaseIntentSignalHistoryList>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_SIGNAL_HISTORY_INFO_H_
