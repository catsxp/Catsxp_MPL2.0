/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ml/pipeline/linear_pipeline_util.h"

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/common/test/file_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/pipeline/pipeline_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::ml {

namespace {
constexpr char kValidSpamClassificationPipeline[] =
    "ml/pipeline/text_processing/linear/valid_spam_classification.fb";
}  // namespace

class CatsxpAdsLinearPipelineUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsLinearPipelineUtilTest, LoadLinearPipelineTest) {
  // Arrange
  std::optional<std::string> contents =
      test::MaybeReadFileToString(kValidSpamClassificationPipeline);
  ASSERT_TRUE(contents);

  // Act
  std::optional<pipeline::PipelineInfo> pipeline = pipeline::LoadLinearPipeline(
      reinterpret_cast<const uint8_t*>(contents->data()), contents->size());

  // Assert
  EXPECT_TRUE(pipeline);
}

}  // namespace catsxp_ads::ml
