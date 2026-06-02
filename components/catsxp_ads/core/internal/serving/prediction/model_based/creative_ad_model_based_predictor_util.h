/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_AD_MODEL_BASED_PREDICTOR_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_AD_MODEL_BASED_PREDICTOR_UTIL_H_

#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/creative_ad_model_based_predictor_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/input_variable/creative_ad_model_based_predictor_input_variable.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/scoring/creative_ad_model_based_predictor_scoring.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/weight/creative_ad_model_based_predictor_weights_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/weight/creative_ad_model_based_predictor_weights_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"

namespace catsxp_ads {

struct UserModelInfo;

template <typename T>
CreativeAdModelBasedPredictorList<T> ComputeCreativeAdModelBasedPredictors(
    const std::vector<T>& creative_ads,
    const UserModelInfo& user_model,
    const AdEventList& ad_events) {
  CreativeAdModelBasedPredictorList<T> creative_ad_predictors;
  creative_ad_predictors.reserve(creative_ads.size());

  const CreativeAdModelBasedPredictorWeightsInfo weights =
      BuildCreativeAdModelBasedPredictorWeights(creative_ads);

  for (const auto& creative_ad : creative_ads) {
    CreativeAdModelBasedPredictorInfo<T> creative_ad_predictor;

    creative_ad_predictor.creative_ad = creative_ad;
    creative_ad_predictor.input_variable =
        ComputeCreativeAdModelBasedPredictorInputVariable(
            creative_ad, user_model, ad_events, weights);
    creative_ad_predictor.score = ComputeCreativeAdModelBasedPredictorScore(
        creative_ad_predictor.input_variable);

    creative_ad_predictors.push_back(creative_ad_predictor);
  }

  return creative_ad_predictors;
}

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_AD_MODEL_BASED_PREDICTOR_UTIL_H_
