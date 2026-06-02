/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ml/ml_prediction_util.h"

#include <algorithm>
#include <cmath>
#include <limits>

namespace catsxp_ads::ml {

PredictionMap Softmax(const PredictionMap& predictions) {
  double maximum = -std::numeric_limits<double>::infinity();
  for (const auto& prediction : predictions) {
    maximum = std::max(maximum, prediction.second);
  }
  PredictionMap softmax_predictions;
  double sum_exp = 0.0;
  for (const auto& prediction : predictions) {
    const double val = std::exp(prediction.second - maximum);
    softmax_predictions[prediction.first] = val;
    sum_exp += val;
  }
  for (auto& prediction : softmax_predictions) {
    prediction.second /= sum_exp;
  }
  return softmax_predictions;
}

}  // namespace catsxp_ads::ml
