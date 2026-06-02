/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_MODEL_NEURAL_NEURAL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_MODEL_NEURAL_NEURAL_H_

#include <cstddef>
#include <optional>

#include "base/memory/raw_ref.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/data/vector_data.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/transformation/ml_types.h"

namespace catsxp_ads {

namespace neural_text_classification::flat {
struct Model;
}  // namespace neural_text_classification::flat

namespace ml {

class NeuralModel final {
 public:
  explicit NeuralModel(const neural_text_classification::flat::Model& model);

  NeuralModel(const NeuralModel&) = delete;
  NeuralModel& operator=(const NeuralModel&) = delete;

  NeuralModel(NeuralModel&&) noexcept;
  NeuralModel& operator=(NeuralModel&&) noexcept;

  ~NeuralModel() = default;

  const neural_text_classification::flat::Model& model() const {
    return *model_;
  }

  std::optional<PredictionMap> Predict(const VectorData& data) const;

  std::optional<PredictionMap> GetTopPredictions(const VectorData& data) const;

  std::optional<PredictionMap> GetTopCountPredictions(const VectorData& data,
                                                      size_t top_count) const;

 private:
  std::optional<PredictionMap> GetTopCountPredictionsImpl(
      const VectorData& data,
      size_t top_count) const;

  raw_ref<const neural_text_classification::flat::Model> model_;
};

}  // namespace ml

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_MODEL_NEURAL_NEURAL_H_
