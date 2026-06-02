/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ml/pipeline/neural_pipeline_util.h"

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/common/test/file_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/pipeline/pipeline_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::ml {

namespace {
constexpr char kOnlyRequiredFieldsNeuralModelPipeline[] =
    "ml/pipeline/text_processing/neural/only_required_fields_neural_model.fb";
}  // namespace

class CatsxpAdsNeuralPipelineUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsNeuralPipelineUtilTest, LoadNeuralPipelineTest) {
  // Arrange
  std::optional<std::string> contents =
      test::MaybeReadFileToString(kOnlyRequiredFieldsNeuralModelPipeline);
  ASSERT_TRUE(contents);

  // Act
  std::optional<pipeline::PipelineInfo> pipeline = pipeline::LoadNeuralPipeline(
      reinterpret_cast<const uint8_t*>(contents->data()), contents->size());

  // Assert
  EXPECT_TRUE(pipeline);
}

}  // namespace catsxp_ads::ml
