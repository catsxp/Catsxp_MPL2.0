/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/scoring/last_seen/creative_ad_model_based_predictor_last_seen_scoring.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/input_variable/last_seen/creative_ad_model_based_predictor_last_seen_input_variable_info.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsCreativeAdModelBasedPredictorLastSeenScoringTest,
     ComputeLastSeenScore) {
  // Arrange
  CreativeAdModelBasedPredictorLastSeenInputVariableInfo
      last_seen_input_variable;
  last_seen_input_variable.value = base::Hours(7);

  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, ComputeLastSeenScore(last_seen_input_variable));
}

TEST(CatsxpAdsCreativeAdModelBasedPredictorLastSeenScoringTest,
     ComputeNeverSeenScore) {
  // Arrange
  CreativeAdModelBasedPredictorLastSeenInputVariableInfo
      last_seen_input_variable;

  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, ComputeLastSeenScore(last_seen_input_variable));
}

TEST(CatsxpAdsCreativeAdModelBasedPredictorLastSeenScoringTest,
     ComputeLastSeenScoreIfExceeds1Day) {
  // Arrange
  CreativeAdModelBasedPredictorLastSeenInputVariableInfo
      last_seen_input_variable;
  last_seen_input_variable.value = base::Days(1) + base::Milliseconds(1);

  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, ComputeLastSeenScore(last_seen_input_variable));
}

}  // namespace catsxp_ads
