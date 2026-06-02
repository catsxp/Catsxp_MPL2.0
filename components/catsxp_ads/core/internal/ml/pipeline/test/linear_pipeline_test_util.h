/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_PIPELINE_TEST_LINEAR_PIPELINE_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_PIPELINE_TEST_LINEAR_PIPELINE_TEST_UTIL_H_

#include <map>
#include <string>
#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/common/resources/flat/text_classification_linear_model_generated.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/data/vector_data.h"

namespace catsxp_ads::ml::pipeline {

class LinearPipelineBufferBuilder final {
 public:
  LinearPipelineBufferBuilder();

  LinearPipelineBufferBuilder(const LinearPipelineBufferBuilder&) = delete;
  LinearPipelineBufferBuilder& operator=(const LinearPipelineBufferBuilder&) =
      delete;

  ~LinearPipelineBufferBuilder();

  LinearPipelineBufferBuilder& CreateClassifier(
      const std::map<std::string, VectorData>& raw_weights,
      const std::map<std::string, float>& raw_biases);

  LinearPipelineBufferBuilder& AddLowercaseTransformation();

  LinearPipelineBufferBuilder& AddHashedNGramsTransformation(
      int bucket_count,
      const std::vector<uint32_t>& subgrams);

  std::string Build(const std::string& language);

 private:
  flatbuffers::FlatBufferBuilder builder_;
  flatbuffers::Offset<linear_text_classification::flat::Classifier> classifier_;
  std::vector<
      flatbuffers::Offset<linear_text_classification::flat::Transformation>>
      transformations_;
};

}  // namespace catsxp_ads::ml::pipeline

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_PIPELINE_TEST_LINEAR_PIPELINE_TEST_UTIL_H_
