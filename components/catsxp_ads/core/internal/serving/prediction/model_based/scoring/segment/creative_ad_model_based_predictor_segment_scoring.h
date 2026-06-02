/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_SCORING_SEGMENT_CREATIVE_AD_MODEL_BASED_PREDICTOR_SEGMENT_SCORING_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_SCORING_SEGMENT_CREATIVE_AD_MODEL_BASED_PREDICTOR_SEGMENT_SCORING_H_

namespace catsxp_ads {

struct CreativeAdModelBasedPredictorSegmentInputVariablesInfo;
struct CreativeAdModelBasedPredictorUntargetedSegmentInputVariableInfo;

// The score computed by these functions is used in the prediction model to
// determine which ad to serve to the user. The higher the score, the more
// likely the ad will be served.

double ComputeSegmentScore(
    const CreativeAdModelBasedPredictorSegmentInputVariablesInfo&
        segment_input_variable);

double ComputeSegmentScore(
    const CreativeAdModelBasedPredictorUntargetedSegmentInputVariableInfo&
        segment_input_variable);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_SCORING_SEGMENT_CREATIVE_AD_MODEL_BASED_PREDICTOR_SEGMENT_SCORING_H_
