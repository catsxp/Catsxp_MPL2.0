/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_PIPELINE_NEURAL_PIPELINE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_PIPELINE_NEURAL_PIPELINE_UTIL_H_

#include <stddef.h>
#include <stdint.h>

#include <optional>

namespace catsxp_ads::ml::pipeline {

struct PipelineInfo;

std::optional<PipelineInfo> LoadNeuralPipeline(const uint8_t* data,
                                               size_t length);

}  // namespace catsxp_ads::ml::pipeline

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_PIPELINE_NEURAL_PIPELINE_UTIL_H_
