/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_signal_history_value_util.h"

#include <string_view>

#include "base/json/values_util.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_signal_history_info.h"

namespace catsxp_ads {

namespace {

constexpr std::string_view kSignaledAtKey = "created_at";
constexpr std::string_view kWeightKey = "weight";
constexpr int kDefaultWeight = 0;

}  // namespace

base::DictValue PurchaseIntentSignalHistoryToDict(
    const PurchaseIntentSignalHistoryInfo& purchase_intent_signal_history) {
  return base::DictValue()
      .Set(kSignaledAtKey, base::TimeToValue(purchase_intent_signal_history.at))
      .Set(kWeightKey, purchase_intent_signal_history.weight);
}

PurchaseIntentSignalHistoryInfo PurchaseIntentSignalHistoryFromDict(
    const base::DictValue& dict) {
  base::Time signaled_at = base::Time();

  if (const auto* const value = dict.Find(kSignaledAtKey)) {
    signaled_at = base::ValueToTime(value).value_or(base::Time());
  }

  const int weight = dict.FindInt(kWeightKey).value_or(kDefaultWeight);

  return {signaled_at, weight};
}

}  // namespace catsxp_ads
