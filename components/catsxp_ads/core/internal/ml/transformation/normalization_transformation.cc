/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ml/transformation/normalization_transformation.h"

#include <utility>

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/data/vector_data.h"

namespace catsxp_ads::ml {

NormalizationTransformation::NormalizationTransformation() = default;

std::unique_ptr<Data> NormalizationTransformation::Apply(
    const std::unique_ptr<Data>& input_data) const {
  CHECK(input_data);

  if (input_data->GetType() != DataType::kVector) {
    return {};
  }

  const auto* const vector_data = static_cast<VectorData*>(input_data.get());

  VectorData vector_data_copy = *vector_data;
  vector_data_copy.Normalize();
  return std::make_unique<VectorData>(std::move(vector_data_copy));
}

}  // namespace catsxp_ads::ml
