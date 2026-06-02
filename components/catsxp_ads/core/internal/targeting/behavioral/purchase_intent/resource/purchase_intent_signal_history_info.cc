/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_signal_history_info.h"

namespace catsxp_ads {

PurchaseIntentSignalHistoryInfo::PurchaseIntentSignalHistoryInfo(base::Time at,
                                                                 int weight)
    : at(at), weight(weight) {}

}  // namespace catsxp_ads
