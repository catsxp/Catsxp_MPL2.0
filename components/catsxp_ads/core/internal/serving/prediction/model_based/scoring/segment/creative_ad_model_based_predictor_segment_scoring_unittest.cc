/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/scoring/segment/creative_ad_model_based_predictor_segment_scoring.h"

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/input_variable/segment/creative_ad_model_based_predictor_segment_input_variables_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/input_variable/segment/creative_ad_model_based_predictor_untargeted_segment_input_variable_info.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsCreativeAdModelBasedPredictorSegmentScoringTest,
     ComputeMatchingChildSegmentScore) {
  // Arrange
  CreativeAdModelBasedPredictorSegmentInputVariablesInfo segment_input_variable;
  segment_input_variable.child_matches.value = true;

  // Act & Assert
  EXPECT_DOUBLE_EQ(1.0, ComputeSegmentScore(segment_input_variable));
}

TEST(CatsxpAdsCreativeAdModelBasedPredictorSegmentScoringTest,
     ComputeMatchingParentSegmentScore) {
  // Arrange
  CreativeAdModelBasedPredictorSegmentInputVariablesInfo segment_input_variable;
  segment_input_variable.parent_matches.value = true;

  // Act & Assert
  EXPECT_DOUBLE_EQ(1.0, ComputeSegmentScore(segment_input_variable));
}

TEST(CatsxpAdsCreativeAdModelBasedPredictorSegmentScoringTest,
     ComputeNonMatchingSegmentScore) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(
      0.0, ComputeSegmentScore(
               CreativeAdModelBasedPredictorSegmentInputVariablesInfo{}));
}

TEST(CatsxpAdsCreativeAdModelBasedPredictorSegmentScoringTest,
     ComputeMatchingUntargetedSegmentScore) {
  // Arrange
  CreativeAdModelBasedPredictorUntargetedSegmentInputVariableInfo
      segment_input_variable;
  segment_input_variable.value = true;

  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0001, ComputeSegmentScore(segment_input_variable));
}

TEST(CatsxpAdsCreativeAdModelBasedPredictorSegmentScoringTest,
     ComputeNonMatchingUntargetedSegmentScore) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(
      0.0,
      ComputeSegmentScore(
          CreativeAdModelBasedPredictorUntargetedSegmentInputVariableInfo{}));
}

}  // namespace catsxp_ads
