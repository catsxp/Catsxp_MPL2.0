/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ml/pipeline/pipeline_info.h"

#include <utility>

namespace catsxp_ads::ml::pipeline {

PipelineInfo::PipelineInfo(std::string locale,
                           TransformationVector transformations,
                           std::optional<LinearModel> linear_model,
                           std::optional<NeuralModel> neural_model)
    : locale(std::move(locale)),
      transformations(std::move(transformations)),
      linear_model(std::move(linear_model)),
      neural_model(std::move(neural_model)) {}

PipelineInfo::PipelineInfo() = default;

PipelineInfo::PipelineInfo(PipelineInfo&& other) noexcept = default;

PipelineInfo& PipelineInfo::operator=(PipelineInfo&& other) noexcept = default;

PipelineInfo::~PipelineInfo() = default;

}  // namespace catsxp_ads::ml::pipeline
