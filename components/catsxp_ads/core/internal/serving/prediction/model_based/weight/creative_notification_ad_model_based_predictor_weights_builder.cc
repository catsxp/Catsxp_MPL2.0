/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/weight/creative_notification_ad_model_based_predictor_weights_builder.h"

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/creative_notification_ad_model_based_predictor_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/weight/creative_ad_model_based_predictor_weights_info.h"

namespace catsxp_ads {

CreativeAdModelBasedPredictorWeightsInfo
BuildCreativeNotificationAdModelBasedPredictorWeights() {
  CreativeAdModelBasedPredictorWeightsInfo weights;

  weights.intent_segment.child =
      kNotificationAdChildIntentSegmentPredictorWeight.Get();
  weights.intent_segment.parent =
      kNotificationAdParentIntentSegmentPredictorWeight.Get();

  weights.latent_interest_segment.child =
      kNotificationAdChildLatentInterestSegmentPredictorWeight.Get();
  weights.latent_interest_segment.parent =
      kNotificationAdParentLatentInterestSegmentPredictorWeight.Get();

  weights.interest_segment.child =
      kNotificationAdChildInterestSegmentPredictorWeight.Get();
  weights.interest_segment.parent =
      kNotificationAdParentInterestSegmentPredictorWeight.Get();

  weights.untargeted_segment =
      kNotificationAdUntargetedSegmentPredictorWeight.Get();

  weights.last_seen_ad = kNotificationAdLastSeenPredictorWeight.Get();

  return weights;
}

}  // namespace catsxp_ads
