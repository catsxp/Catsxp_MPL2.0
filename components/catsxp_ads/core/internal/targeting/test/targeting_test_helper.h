/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_TEST_TARGETING_TEST_HELPER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_TEST_TARGETING_TEST_HELPER_H_

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/test/purchase_intent_test_helper.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/test/text_classification_test_helper.h"

namespace catsxp_ads {

struct IntentUserModelInfo;
struct InterestUserModelInfo;
struct LatentInterestUserModelInfo;
struct UserModelInfo;

namespace test {

class TargetingHelper final {
 public:
  TargetingHelper();

  TargetingHelper(const TargetingHelper&) = delete;
  TargetingHelper& operator=(const TargetingHelper&) = delete;

  ~TargetingHelper();

  void Simulate();
  static UserModelInfo Expectation();

  void SimulateIntent();
  static IntentUserModelInfo IntentExpectation();

  void SimulateLatentInterest();
  static LatentInterestUserModelInfo LatentInterestExpectation();

  void SimulateInterest();
  static InterestUserModelInfo InterestExpectation();

 private:
  PurchaseIntentHelper purchase_intent_;
  TextClassificationHelper text_classification_;
};

}  // namespace test

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_TEST_TARGETING_TEST_HELPER_H_
