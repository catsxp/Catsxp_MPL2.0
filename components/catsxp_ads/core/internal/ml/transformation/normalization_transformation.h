/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_NORMALIZATION_TRANSFORMATION_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_NORMALIZATION_TRANSFORMATION_H_

#include <memory>

#include "catsxp/components/catsxp_ads/core/internal/ml/transformation/transformation.h"

namespace catsxp_ads::ml {

class NormalizationTransformation final : public Transformation {
 public:
  NormalizationTransformation();

  // Transformation:
  std::unique_ptr<Data> Apply(
      const std::unique_ptr<Data>& input_data) const override;
};

}  // namespace catsxp_ads::ml

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_NORMALIZATION_TRANSFORMATION_H_
