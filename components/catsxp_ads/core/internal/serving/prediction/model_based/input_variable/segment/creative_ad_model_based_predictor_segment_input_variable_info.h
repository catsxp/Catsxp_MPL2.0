/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_SEGMENT_CREATIVE_AD_MODEL_BASED_PREDICTOR_SEGMENT_INPUT_VARIABLE_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_SEGMENT_CREATIVE_AD_MODEL_BASED_PREDICTOR_SEGMENT_INPUT_VARIABLE_INFO_H_

namespace catsxp_ads {

struct CreativeAdModelBasedPredictorSegmentInputVariableInfo final {
  bool operator==(const CreativeAdModelBasedPredictorSegmentInputVariableInfo&)
      const = default;

  // Whether the user segment matches the creative ad.
  bool value = false;
  double weight = 1.0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_SEGMENT_CREATIVE_AD_MODEL_BASED_PREDICTOR_SEGMENT_INPUT_VARIABLE_INFO_H_
