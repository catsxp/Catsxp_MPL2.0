/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/scoring/segment/creative_ad_model_based_predictor_segment_scoring.h"

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/input_variable/segment/creative_ad_model_based_predictor_segment_input_variables_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/input_variable/segment/creative_ad_model_based_predictor_untargeted_segment_input_variable_info.h"

namespace catsxp_ads {

namespace {
constexpr double kNoMatchScore = 0.0;
}  // namespace

double ComputeSegmentScore(
    const CreativeAdModelBasedPredictorSegmentInputVariablesInfo&
        segment_input_variable) {
  // Compute the score of a segment based on whether the segment matches a child
  // or parent segment. If there is no match, do not serve the ad.

  if (segment_input_variable.child_matches.value) {
    return segment_input_variable.child_matches.weight;
  }

  if (segment_input_variable.parent_matches.value) {
    return segment_input_variable.parent_matches.weight;
  }

  return kNoMatchScore;
}

double ComputeSegmentScore(
    const CreativeAdModelBasedPredictorUntargetedSegmentInputVariableInfo&
        segment_input_variable) {
  // Compute the score of a segment based on whether the segment matches an
  // untargeted segment. If there is no match, do not serve the ad.
  return segment_input_variable.value ? segment_input_variable.weight
                                      : kNoMatchScore;
}

}  // namespace catsxp_ads
