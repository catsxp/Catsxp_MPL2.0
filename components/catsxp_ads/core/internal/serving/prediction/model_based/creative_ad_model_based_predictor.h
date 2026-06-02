/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_AD_MODEL_BASED_PREDICTOR_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_AD_MODEL_BASED_PREDICTOR_H_

#include <optional>
#include <vector>

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/creative_ad_model_based_predictor_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/creative_ad_model_based_predictor_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/sampling/creative_ad_model_based_predictor_sampling.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"

namespace catsxp_ads {

struct UserModelInfo;

template <typename T>
std::optional<T> MaybePredictCreativeAd(const std::vector<T>& creative_ads,
                                        const UserModelInfo& user_model,
                                        const AdEventList& ad_events) {
  CHECK(!creative_ads.empty());

  const CreativeAdModelBasedPredictorList<T> creative_ad_predictors =
      ComputeCreativeAdModelBasedPredictors(creative_ads, user_model,
                                            ad_events);

  return MaybeSampleCreativeAd(creative_ad_predictors);
}

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_AD_MODEL_BASED_PREDICTOR_H_
