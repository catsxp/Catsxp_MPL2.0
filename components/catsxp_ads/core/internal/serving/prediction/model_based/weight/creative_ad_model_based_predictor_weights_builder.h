/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_WEIGHT_CREATIVE_AD_MODEL_BASED_PREDICTOR_WEIGHTS_BUILDER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_WEIGHT_CREATIVE_AD_MODEL_BASED_PREDICTOR_WEIGHTS_BUILDER_H_

#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/weight/creative_ad_model_based_predictor_weights_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/weight/creative_new_tab_page_ad_model_based_predictor_weights_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/weight/creative_notification_ad_model_based_predictor_weights_builder.h"

namespace catsxp_ads {

template <typename T>
struct CreativeAdModelBasedPredictorWeightsBuilder;

template <>
struct CreativeAdModelBasedPredictorWeightsBuilder<CreativeNewTabPageAdInfo> {
  static CreativeAdModelBasedPredictorWeightsInfo build() {
    return BuildCreativeNewTabPageAdModelBasedPredictorWeights();
  }
};

template <>
struct CreativeAdModelBasedPredictorWeightsBuilder<CreativeNotificationAdInfo> {
  static CreativeAdModelBasedPredictorWeightsInfo build() {
    return BuildCreativeNotificationAdModelBasedPredictorWeights();
  }
};

template <typename T>
CreativeAdModelBasedPredictorWeightsInfo
BuildCreativeAdModelBasedPredictorWeights(
    const std::vector<T>& /*creative_ads*/) {
  return CreativeAdModelBasedPredictorWeightsBuilder<T>::build();
}

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_WEIGHT_CREATIVE_AD_MODEL_BASED_PREDICTOR_WEIGHTS_BUILDER_H_
