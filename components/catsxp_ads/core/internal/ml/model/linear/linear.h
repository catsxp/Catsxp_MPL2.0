/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_MODEL_LINEAR_LINEAR_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_MODEL_LINEAR_LINEAR_H_

#include <cstddef>
#include <optional>

#include "base/memory/raw_ref.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/data/vector_data.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/transformation/ml_types.h"

namespace catsxp_ads {

namespace linear_text_classification::flat {
struct Model;
}  // namespace linear_text_classification::flat

namespace ml {

class LinearModel final {
 public:
  explicit LinearModel(const linear_text_classification::flat::Model& model);

  LinearModel(const LinearModel&) = delete;
  LinearModel& operator=(const LinearModel&) = delete;

  LinearModel(LinearModel&&) noexcept;
  LinearModel& operator=(LinearModel&&) noexcept;

  ~LinearModel() = default;

  std::optional<PredictionMap> Predict(const VectorData& data) const;

  std::optional<PredictionMap> GetTopPredictions(const VectorData& data) const;

  std::optional<PredictionMap> GetTopCountPredictions(const VectorData& data,
                                                      size_t top_count) const;

 private:
  std::optional<PredictionMap> GetTopCountPredictionsImpl(
      const VectorData& data,
      std::optional<size_t> top_count) const;

  raw_ref<const linear_text_classification::flat::Model> model_;
};

}  // namespace ml

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_MODEL_LINEAR_LINEAR_H_
