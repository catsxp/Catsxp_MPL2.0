/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/scoring/creative_ad_model_based_predictor_scoring.h"

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/input_variable/creative_ad_model_based_predictor_input_variable_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/scoring/last_seen/creative_ad_model_based_predictor_last_seen_scoring.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/scoring/segment/creative_ad_model_based_predictor_segment_scoring.h"

namespace catsxp_ads {

double ComputeCreativeAdModelBasedPredictorScore(
    const CreativeAdModelBasedPredictorInputVariableInfo& input_variable) {
  return ComputeSegmentScore(input_variable.intent_segment) +
         ComputeSegmentScore(input_variable.latent_interest_segment) +
         ComputeSegmentScore(input_variable.interest_segment) +
         ComputeSegmentScore(input_variable.untargeted_segment) +
         ComputeLastSeenScore(input_variable.last_seen_ad);
}

}  // namespace catsxp_ads
