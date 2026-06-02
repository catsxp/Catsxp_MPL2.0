/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_PIPELINE_TEXT_PROCESSING_TEXT_PROCESSING_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_PIPELINE_TEXT_PROCESSING_TEXT_PROCESSING_H_

#include <memory>
#include <optional>
#include <string>

#include "base/files/memory_mapped_file.h"
#include "base/types/expected.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/data/vector_data.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/model/linear/linear.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/model/neural/neural.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/transformation/transformation.h"

namespace base {
class File;
}  // namespace base

namespace catsxp_ads::ml::pipeline {

struct PipelineInfo;

class TextProcessing final {
 public:
  TextProcessing();
  TextProcessing(TransformationVector transformations,
                 std::optional<LinearModel> linear_model);

  TextProcessing(const TextProcessing&) = delete;
  TextProcessing& operator=(const TextProcessing&) = delete;

  TextProcessing(TextProcessing&&) noexcept;
  TextProcessing& operator=(TextProcessing&&) noexcept;

  ~TextProcessing();

  bool IsInitialized() const { return is_initialized_; }
  bool IsNeuralPipline() const { return neural_model_.has_value(); }

  base::expected<bool, std::string> LoadPipeline(base::File file);
  void SetPipeline(PipelineInfo pipeline);
  bool SetPipeline(base::File file);

  std::optional<PredictionMap> Predict(const VectorData* vector_data) const;

  std::optional<PredictionMap> Apply(
      std::unique_ptr<Data> mutable_input_data) const;

  std::optional<PredictionMap> GetPredictions(const std::string& text) const;

  std::optional<PredictionMap> GetTopPredictions(const std::string& text) const;

  std::optional<PredictionMap> ClassifyPage(const std::string& text) const;

 private:
  bool is_initialized_ = false;

  std::string locale_ = "en";

  std::unique_ptr<base::MemoryMappedFile> pipeline_mapped_file_;
  TransformationVector transformations_;
  std::optional<LinearModel> linear_model_;
  std::optional<NeuralModel> neural_model_;
};

}  // namespace catsxp_ads::ml::pipeline

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_PIPELINE_TEXT_PROCESSING_TEXT_PROCESSING_H_
