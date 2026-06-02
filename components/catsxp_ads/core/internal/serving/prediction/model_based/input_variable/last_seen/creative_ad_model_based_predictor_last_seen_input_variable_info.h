/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_LAST_SEEN_CREATIVE_AD_MODEL_BASED_PREDICTOR_LAST_SEEN_INPUT_VARIABLE_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_LAST_SEEN_CREATIVE_AD_MODEL_BASED_PREDICTOR_LAST_SEEN_INPUT_VARIABLE_INFO_H_

#include <optional>

#include "base/time/time.h"

namespace catsxp_ads {

struct CreativeAdModelBasedPredictorLastSeenInputVariableInfo final {
  bool operator==(const CreativeAdModelBasedPredictorLastSeenInputVariableInfo&)
      const = default;

  // The time delta since the last time the user saw an ad.
  std::optional<base::TimeDelta> value;
  double weight = 0.0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_LAST_SEEN_CREATIVE_AD_MODEL_BASED_PREDICTOR_LAST_SEEN_INPUT_VARIABLE_INFO_H_
