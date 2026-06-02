/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_SIGNAL_HISTORY_VALUE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_SIGNAL_HISTORY_VALUE_UTIL_H_

#include "base/values.h"

namespace catsxp_ads {

struct PurchaseIntentSignalHistoryInfo;

base::DictValue PurchaseIntentSignalHistoryToDict(
    const PurchaseIntentSignalHistoryInfo& purchase_intent_signal_history);

PurchaseIntentSignalHistoryInfo PurchaseIntentSignalHistoryFromDict(
    const base::DictValue& dict);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_SIGNAL_HISTORY_VALUE_UTIL_H_
