/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/model/purchase_intent_model_segment_scoring.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/deprecated/client/client_state_manager.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/model/purchase_intent_model.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/model/purchase_intent_signal_info.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/purchase_intent_feature.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsPurchaseIntentModelSegmentScoringTest : public test::TestBase {};

TEST_F(CatsxpAdsPurchaseIntentModelSegmentScoringTest,
       ComputePurchaseIntentSignalHistorySegmentScores) {
  // Arrange
  const base::Time decayed_at = test::Now() - kPurchaseIntentTimeWindow.Get();

  const base::Time on_cusp_at =
      test::Now() - (kPurchaseIntentTimeWindow.Get() - base::Milliseconds(1));

  const PurchaseIntentSignalList purchase_intent_signals = {
      {decayed_at, {"segment 3"}, 1},
      {on_cusp_at, {"segment 4"}, 4},
      {test::Now() - base::Minutes(2), {"segment 1", "segment 2"}, 3},
      {test::Now() - base::Minutes(1), {"segment 1"}, 2},
      {test::Now(), {"segment 5"}, 5}};

  for (const auto& purchase_intent_signal : purchase_intent_signals) {
    BuyPurchaseIntentSignal(purchase_intent_signal);
  }

  const PurchaseIntentSignalHistoryMap& purchase_intent_signal_history =
      ClientStateManager::GetInstance().GetPurchaseIntentSignalHistory();

  // Act
  const std::multimap</*score*/ int, /*segment*/ std::string>
      purchase_intent_signal_history_segment_scores =
          ComputePurchaseIntentSignalHistorySegmentScores(
              purchase_intent_signal_history);

  // Assert
  const std::multimap</*score*/ int, /*segment*/ std::string>
      expected_purchase_intent_signal_history_segment_scores = {
          {0, "segment 3"},
          {3, "segment 2"},
          {4, "segment 4"},
          {5, "segment 1"},
          {5, "segment 5"}};
  EXPECT_EQ(expected_purchase_intent_signal_history_segment_scores,
            purchase_intent_signal_history_segment_scores);
}

TEST_F(CatsxpAdsPurchaseIntentModelSegmentScoringTest,
       ComputeEmptyPurchaseIntentSignalHistorySegmentScores) {
  // Act
  const std::multimap</*score*/ int, /*segment*/ std::string> segment_scores =
      ComputePurchaseIntentSignalHistorySegmentScores(/*signal_history=*/{});

  // Assert
  EXPECT_THAT(segment_scores, ::testing::IsEmpty());
}

}  // namespace catsxp_ads
