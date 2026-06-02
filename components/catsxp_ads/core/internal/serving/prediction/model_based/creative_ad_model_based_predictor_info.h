/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_AD_MODEL_BASED_PREDICTOR_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_AD_MODEL_BASED_PREDICTOR_INFO_H_

#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/input_variable/creative_ad_model_based_predictor_input_variable_info.h"

namespace catsxp_ads {

template <typename T>
struct CreativeAdModelBasedPredictorInfo final {
  bool operator==(const CreativeAdModelBasedPredictorInfo<T>&) const = default;

  T creative_ad;
  CreativeAdModelBasedPredictorInputVariableInfo input_variable;
  double score = 0.0;
};

template <typename T>
using CreativeAdModelBasedPredictorList =
    std::vector<CreativeAdModelBasedPredictorInfo<T>>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_AD_MODEL_BASED_PREDICTOR_INFO_H_
