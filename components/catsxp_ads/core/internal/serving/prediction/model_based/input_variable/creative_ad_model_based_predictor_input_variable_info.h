/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_CREATIVE_AD_MODEL_BASED_PREDICTOR_INPUT_VARIABLE_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_CREATIVE_AD_MODEL_BASED_PREDICTOR_INPUT_VARIABLE_INFO_H_

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/input_variable/last_seen/creative_ad_model_based_predictor_last_seen_input_variable_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/input_variable/segment/creative_ad_model_based_predictor_segment_input_variables_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/input_variable/segment/creative_ad_model_based_predictor_untargeted_segment_input_variable_info.h"

namespace catsxp_ads {

struct CreativeAdModelBasedPredictorInputVariableInfo final {
  bool operator==(const CreativeAdModelBasedPredictorInputVariableInfo&) const =
      default;

  // Whether the creative ad is targeted to the user's intent.
  CreativeAdModelBasedPredictorSegmentInputVariablesInfo intent_segment;

  // Whether the creative ad is targeted to the user's latent interest.
  CreativeAdModelBasedPredictorSegmentInputVariablesInfo
      latent_interest_segment;

  // Whether the creative ad is targeted to the user's interest.
  CreativeAdModelBasedPredictorSegmentInputVariablesInfo interest_segment;

  // Whether the creative ad is untargeted.
  CreativeAdModelBasedPredictorUntargetedSegmentInputVariableInfo
      untargeted_segment;

  // The last time the user saw this ad.
  CreativeAdModelBasedPredictorLastSeenInputVariableInfo last_seen_ad;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_CREATIVE_AD_MODEL_BASED_PREDICTOR_INPUT_VARIABLE_INFO_H_
