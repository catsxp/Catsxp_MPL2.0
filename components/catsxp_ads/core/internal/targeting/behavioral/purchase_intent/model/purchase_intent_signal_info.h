/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_MODEL_PURCHASE_INTENT_SIGNAL_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_MODEL_PURCHASE_INTENT_SIGNAL_INFO_H_

#include <vector>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"

namespace catsxp_ads {

struct PurchaseIntentSignalInfo final {
  PurchaseIntentSignalInfo();

  PurchaseIntentSignalInfo(base::Time at, SegmentList segments, int weight);

  PurchaseIntentSignalInfo(const PurchaseIntentSignalInfo&);
  PurchaseIntentSignalInfo& operator=(const PurchaseIntentSignalInfo&);

  PurchaseIntentSignalInfo(PurchaseIntentSignalInfo&&) noexcept;
  PurchaseIntentSignalInfo& operator=(PurchaseIntentSignalInfo&&) noexcept;

  ~PurchaseIntentSignalInfo();

  base::Time at;
  SegmentList segments;
  int weight = 0;
};

using PurchaseIntentSignalList = std::vector<PurchaseIntentSignalInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_MODEL_PURCHASE_INTENT_SIGNAL_INFO_H_
