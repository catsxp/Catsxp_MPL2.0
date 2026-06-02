/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_PIPELINE_TEST_NEURAL_PIPELINE_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_PIPELINE_TEST_NEURAL_PIPELINE_TEST_UTIL_H_

#include <map>
#include <string>
#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/common/resources/flat/text_classification_neural_model_generated.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/data/vector_data.h"

namespace catsxp_ads::ml::pipeline {

class NeuralPipelineBufferBuilder final {
 public:
  NeuralPipelineBufferBuilder();

  NeuralPipelineBufferBuilder(const NeuralPipelineBufferBuilder&) = delete;
  NeuralPipelineBufferBuilder& operator=(const NeuralPipelineBufferBuilder&) =
      delete;

  ~NeuralPipelineBufferBuilder();

  NeuralPipelineBufferBuilder& CreateClassifier(
      const std::vector<std::vector<VectorData>>& raw_matrices,
      const std::vector<std::string>& raw_activation_functions,
      const std::vector<std::string>& raw_segments);

  NeuralPipelineBufferBuilder& AddMappedTokensTransformation(
      int vector_dimension,
      const std::map<std::string, std::vector<uint16_t>>&
          token_categories_mapping);

  std::string Build(const std::string& language);

 private:
  flatbuffers::FlatBufferBuilder builder_;
  flatbuffers::Offset<neural_text_classification::flat::Classifier> classifier_;
  std::vector<
      flatbuffers::Offset<neural_text_classification::flat::Transformation>>
      transformations_;
};

}  // namespace catsxp_ads::ml::pipeline

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_PIPELINE_TEST_NEURAL_PIPELINE_TEST_UTIL_H_
