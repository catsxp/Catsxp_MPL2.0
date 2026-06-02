/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_SEGMENT_CREATIVE_AD_MODEL_BASED_PREDICTOR_UNTARGETED_SEGMENT_INPUT_VARIABLE_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_SEGMENT_CREATIVE_AD_MODEL_BASED_PREDICTOR_UNTARGETED_SEGMENT_INPUT_VARIABLE_INFO_H_

namespace catsxp_ads {

struct CreativeAdModelBasedPredictorUntargetedSegmentInputVariableInfo final {
  bool operator==(
      const CreativeAdModelBasedPredictorUntargetedSegmentInputVariableInfo&)
      const = default;

  // Whether the creative ad is untargeted.
  bool value = false;
  double weight = 0.0001;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_SEGMENT_CREATIVE_AD_MODEL_BASED_PREDICTOR_UNTARGETED_SEGMENT_INPUT_VARIABLE_INFO_H_
