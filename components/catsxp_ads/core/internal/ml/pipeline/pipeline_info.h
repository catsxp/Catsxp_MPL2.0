/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_PIPELINE_PIPELINE_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_PIPELINE_PIPELINE_INFO_H_

#include <optional>
#include <string>

#include "catsxp/components/catsxp_ads/core/internal/ml/model/linear/linear.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/model/neural/neural.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/transformation/transformation.h"

namespace catsxp_ads::ml::pipeline {

struct PipelineInfo final {
  PipelineInfo();
  PipelineInfo(std::string locale,
               TransformationVector transformations,
               std::optional<LinearModel> linear_model,
               std::optional<NeuralModel> neural_model);

  PipelineInfo(PipelineInfo&&) noexcept;
  PipelineInfo& operator=(PipelineInfo&&) noexcept;

  ~PipelineInfo();

  std::string locale;
  TransformationVector transformations;
  std::optional<LinearModel> linear_model;
  std::optional<NeuralModel> neural_model;
};

}  // namespace catsxp_ads::ml::pipeline

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_PIPELINE_PIPELINE_INFO_H_
