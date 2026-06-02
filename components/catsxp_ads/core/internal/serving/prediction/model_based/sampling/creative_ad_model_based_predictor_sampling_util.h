/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_SAMPLING_CREATIVE_AD_MODEL_BASED_PREDICTOR_SAMPLING_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_SAMPLING_CREATIVE_AD_MODEL_BASED_PREDICTOR_SAMPLING_UTIL_H_

#include <numeric>

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/creative_ad_model_based_predictor_info.h"

namespace catsxp_ads {

template <typename T>
double CalculateNormalizingConstantForCreativeAdModelBasedPredictors(
    const CreativeAdModelBasedPredictorList<T>& creative_ad_predictors) {
  return std::accumulate(
      creative_ad_predictors.cbegin(), creative_ad_predictors.cend(), 0.0,
      [](double normalizing_constant,
         const CreativeAdModelBasedPredictorList<T>::value_type&
             creative_ad_predictor) {
        return normalizing_constant + creative_ad_predictor.score;
      });
}

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_SAMPLING_CREATIVE_AD_MODEL_BASED_PREDICTOR_SAMPLING_UTIL_H_
