/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/model/purchase_intent_model.h"

#include <map>
#include <string>

#include "catsxp/components/catsxp_ads/core/internal/deprecated/client/client_state_manager.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/model/purchase_intent_model_segment_predictor.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/model/purchase_intent_model_segment_scoring.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/model/purchase_intent_signal_info.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_signal_history_info.h"

namespace catsxp_ads {

void BuyPurchaseIntentSignal(
    const PurchaseIntentSignalInfo& purchase_intent_signal) {
  const PurchaseIntentSignalHistoryInfo signal_history(
      purchase_intent_signal.at, purchase_intent_signal.weight);

  for (const auto& segment : purchase_intent_signal.segments) {
    ClientStateManager::GetInstance()
        .AppendToPurchaseIntentSignalHistoryForSegment(segment, signal_history);
  }
}

SegmentList GetPurchaseIntentSegments() {
  const PurchaseIntentSignalHistoryMap& signal_history =
      ClientStateManager::GetInstance().GetPurchaseIntentSignalHistory();

  const std::multimap</*score*/ int, /*segment*/ std::string> segment_scores =
      ComputePurchaseIntentSignalHistorySegmentScores(signal_history);

  return PredictPurchaseIntentSegments(segment_scores);
}

}  // namespace catsxp_ads
