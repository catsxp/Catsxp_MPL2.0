/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/weight/segment/test/creative_ad_model_based_predictor_segment_weight_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/weight/creative_ad_model_based_predictor_weights_info.h"

namespace catsxp_ads::test {

CreativeAdModelBasedPredictorWeightsInfo
BuildCreativeAdModelBasedPredictorWeights() {
  CreativeAdModelBasedPredictorWeightsInfo weights;

  weights.intent_segment.child = 1.0;
  weights.intent_segment.parent = 1.0;

  weights.latent_interest_segment.child = 1.0;
  weights.latent_interest_segment.parent = 1.0;

  weights.interest_segment.child = 1.0;
  weights.interest_segment.parent = 1.0;

  weights.untargeted_segment = 0.0001;

  weights.last_seen_ad = 0.0;

  return weights;
}
}  // namespace catsxp_ads::test
