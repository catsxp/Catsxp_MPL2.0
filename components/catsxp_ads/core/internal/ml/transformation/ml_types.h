/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

// Prediction type alias separated from the Transformation base class so that
// consumers needing only PredictionMap do not pull in the class definition.

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_ML_TYPES_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_ML_TYPES_H_

#include <map>
#include <string>

namespace catsxp_ads::ml {

using PredictionMap = std::map</*class*/ std::string, /*prediction*/ double>;

}  // namespace catsxp_ads::ml

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_ML_TYPES_H_
