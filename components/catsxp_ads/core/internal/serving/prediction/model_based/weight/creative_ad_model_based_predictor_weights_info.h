/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_WEIGHT_CREATIVE_AD_MODEL_BASED_PREDICTOR_WEIGHTS_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_WEIGHT_CREATIVE_AD_MODEL_BASED_PREDICTOR_WEIGHTS_INFO_H_

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/weight/segment/creative_ad_model_based_predictor_segment_weight_info.h"

namespace catsxp_ads {

struct CreativeAdModelBasedPredictorWeightsInfo final {
  bool operator==(const CreativeAdModelBasedPredictorWeightsInfo&) const =
      default;

  CreativeAdModelBasedPredictorSegmentWeightInfo intent_segment;
  CreativeAdModelBasedPredictorSegmentWeightInfo latent_interest_segment;
  CreativeAdModelBasedPredictorSegmentWeightInfo interest_segment;

  double untargeted_segment = 0.0;

  double last_seen_ad = 0.0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_WEIGHT_CREATIVE_AD_MODEL_BASED_PREDICTOR_WEIGHTS_INFO_H_
