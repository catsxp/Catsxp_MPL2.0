/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/model/purchase_intent_model_segment_scoring.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/purchase_intent_feature.h"

namespace catsxp_ads {

namespace {

int ComputePurchaseIntentSignalHistoryScore(
    const PurchaseIntentSignalHistoryList& signal_history,
    base::Time now,
    base::TimeDelta time_window,
    int signal_level) {
  int score = 0;

  for (const auto& signal : signal_history) {
    const base::Time decay_signal_at = signal.at + time_window;
    if (now >= decay_signal_at) {
      break;
    }

    score += signal_level * signal.weight;
  }

  return score;
}

}  // namespace

std::multimap</*score*/ int, /*segment*/ std::string>
ComputePurchaseIntentSignalHistorySegmentScores(
    const PurchaseIntentSignalHistoryMap& signal_history) {
  const base::Time now = base::Time::Now();

  const base::TimeDelta time_window = kPurchaseIntentTimeWindow.Get();

  const int signal_level = kPurchaseIntentSignalLevel.Get();

  std::multimap<int, std::string> segment_scores;

  for (const auto& [segment, history] : signal_history) {
    segment_scores.insert({ComputePurchaseIntentSignalHistoryScore(
                               history, now, time_window, signal_level),
                           segment});
  }

  return segment_scores;
}

}  // namespace catsxp_ads
