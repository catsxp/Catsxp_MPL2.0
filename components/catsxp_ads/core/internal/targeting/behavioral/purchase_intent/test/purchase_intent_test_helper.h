/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_TEST_PURCHASE_INTENT_TEST_HELPER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_TEST_PURCHASE_INTENT_TEST_HELPER_H_

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/purchase_intent_processor.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_resource.h"

namespace catsxp_ads::test {

class PurchaseIntentHelper final {
 public:
  PurchaseIntentHelper();

  PurchaseIntentHelper(const PurchaseIntentHelper&) = delete;
  PurchaseIntentHelper& operator=(const PurchaseIntentHelper&) = delete;

  ~PurchaseIntentHelper();

  void Simulate();

  static SegmentList Expectation();

 private:
  PurchaseIntentResource resource_;
  PurchaseIntentProcessor processor_;
};

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_TEST_PURCHASE_INTENT_TEST_HELPER_H_
