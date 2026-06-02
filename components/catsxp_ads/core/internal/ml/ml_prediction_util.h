/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_ML_PREDICTION_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_ML_PREDICTION_UTIL_H_

#include "catsxp/components/catsxp_ads/core/internal/ml/transformation/ml_types.h"

namespace catsxp_ads::ml {

PredictionMap Softmax(const PredictionMap& predictions);

}  // namespace catsxp_ads::ml

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_ML_PREDICTION_UTIL_H_
