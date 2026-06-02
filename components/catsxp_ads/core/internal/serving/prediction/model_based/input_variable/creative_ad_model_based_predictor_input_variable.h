/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_CREATIVE_AD_MODEL_BASED_PREDICTOR_INPUT_VARIABLE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_CREATIVE_AD_MODEL_BASED_PREDICTOR_INPUT_VARIABLE_H_

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/input_variable/creative_ad_model_based_predictor_input_variable_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/input_variable/creative_ad_model_based_predictor_input_variable_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/weight/creative_ad_model_based_predictor_weights_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"

namespace catsxp_ads {

struct UserModelInfo;

template <typename T>
CreativeAdModelBasedPredictorInputVariableInfo
ComputeCreativeAdModelBasedPredictorInputVariable(
    const T& creative_ad,
    const UserModelInfo& user_model,
    const AdEventList& ad_events,
    const CreativeAdModelBasedPredictorWeightsInfo& weights) {
  CreativeAdModelBasedPredictorInputVariableInfo input_variable;

  input_variable.intent_segment =
      ComputeCreativeAdModelBasedPredictorIntentSegmentInputVariable(
          user_model, creative_ad.segment, weights.intent_segment);

  input_variable.latent_interest_segment =
      ComputeCreativeAdModelBasedPredictorLatentInterestSegmentInputVariable(
          user_model, creative_ad.segment, weights.latent_interest_segment);

  input_variable.interest_segment =
      ComputeCreativeAdModelBasedPredictorInterestSegmentInputVariable(
          user_model, creative_ad.segment, weights.interest_segment);

  input_variable.untargeted_segment =
      ComputeCreativeAdModelBasedPredictorUntargetedSegmentInputVariable(
          creative_ad.segment, weights.untargeted_segment);

  input_variable.last_seen_ad =
      ComputeCreativeAdModelBasedPredictorLastSeenAdInputVariable(
          creative_ad, ad_events, weights.last_seen_ad);

  return input_variable;
}

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_CREATIVE_AD_MODEL_BASED_PREDICTOR_INPUT_VARIABLE_H_
