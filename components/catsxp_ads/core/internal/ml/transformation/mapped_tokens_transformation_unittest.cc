/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ml/transformation/mapped_tokens_transformation.h"

#include <cstddef>
#include <string>
#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/common/resources/flat/text_classification_neural_model_generated.h"
#include "catsxp/components/catsxp_ads/core/internal/common/resources/flat/text_classification_neural_transformation_generated.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/data/text_data.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/data/vector_data.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/pipeline/test/neural_pipeline_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::ml {

class CatsxpAdsMappedTokensTransformationTest : public test::TestBase {
 public:
  std::optional<MappedTokensTransformation> BuildMappedTokensTransformation(
      int vector_dimension,
      const std::map<std::string, std::vector<uint16_t>>&
          token_categories_mapping) {
    buffer_ = pipeline::NeuralPipelineBufferBuilder()
                  .CreateClassifier(/*raw_matrices=*/{},
                                    /*raw_activation_functions=*/{},
                                    /*raw_segments=*/{})
                  .AddMappedTokensTransformation(vector_dimension,
                                                 token_categories_mapping)
                  .Build(/*language=*/"en");

    flatbuffers::Verifier verifier(
        reinterpret_cast<const uint8_t*>(buffer_.data()), buffer_.size());
    if (!neural_text_classification::flat::VerifyModelBuffer(verifier)) {
      return std::nullopt;
    }

    const auto* const raw_model =
        neural_text_classification::flat::GetModel(buffer_.data());
    if (!raw_model || !raw_model->transformations()) {
      return std::nullopt;
    }

    const auto* const transformation_entry =
        raw_model->transformations()->Get(0);
    if (!transformation_entry) {
      return std::nullopt;
    }

    const auto* transformation =
        transformation_entry->transformation_as_MappedTokenTransformation();
    if (!transformation) {
      return std::nullopt;
    }

    return MappedTokensTransformation(*transformation);
  }

 private:
  std::string buffer_;
};

TEST_F(CatsxpAdsMappedTokensTransformationTest, ToMappedTokens) {
  // Arrange
  constexpr double kTolerance = 1e-6;

  constexpr char kTestString[] = "this is a simple test string";
  std::unique_ptr<Data> data = std::make_unique<TextData>(kTestString);

  int vector_dimension = 6;
  std::map<std::string, std::vector<uint16_t>> token_categories_mapping = {
      {"is", {1}}, {"this", {5}}, {"test-string", {0, 3}}, {"simple", {1, 4}}};

  std::optional<MappedTokensTransformation> to_mapped_tokens =
      BuildMappedTokensTransformation(vector_dimension,
                                      token_categories_mapping);
  ASSERT_TRUE(to_mapped_tokens);

  // Act
  data = to_mapped_tokens->Apply(data);
  ASSERT_EQ(DataType::kVector, data->GetType());
  const VectorData* const transformed_vector_data =
      static_cast<VectorData*>(data.get());

  const std::vector<float> transformed_vector_values =
      transformed_vector_data->GetDenseData();
  ASSERT_TRUE(transformed_vector_values.size() ==
              static_cast<size_t>(vector_dimension));

  // Assert
  EXPECT_LT(std::fabs(1.0 - transformed_vector_values.at(0)), kTolerance);
  EXPECT_LT(std::fabs(2.0 - transformed_vector_values.at(1)), kTolerance);
  EXPECT_LT(std::fabs(0.0 - transformed_vector_values.at(2)), kTolerance);
  EXPECT_LT(std::fabs(1.0 - transformed_vector_values.at(3)), kTolerance);
  EXPECT_LT(std::fabs(1.0 - transformed_vector_values.at(4)), kTolerance);
  EXPECT_LT(std::fabs(1.0 - transformed_vector_values.at(5)), kTolerance);
}

TEST_F(CatsxpAdsMappedTokensTransformationTest, EmptyText) {
  // Arrange
  constexpr double kTolerance = 1e-6;

  constexpr char kTestString[] = "";
  std::unique_ptr<Data> data = std::make_unique<TextData>(kTestString);

  int vector_dimension = 6;
  std::map<std::string, std::vector<uint16_t>> token_categories_mapping = {
      {"is", {1}}, {"this", {5}}, {"test-string", {0, 3}}, {"simple", {1, 4}}};

  std::optional<MappedTokensTransformation> to_mapped_tokens =
      BuildMappedTokensTransformation(vector_dimension,
                                      token_categories_mapping);
  ASSERT_TRUE(to_mapped_tokens);

  // Act
  data = to_mapped_tokens->Apply(data);
  ASSERT_EQ(DataType::kVector, data->GetType());
  const VectorData* const transformed_vector_data =
      static_cast<VectorData*>(data.get());

  const std::vector<float> transformed_vector_values =
      transformed_vector_data->GetDenseData();
  ASSERT_TRUE(transformed_vector_values.size() ==
              static_cast<size_t>(vector_dimension));

  // Assert
  EXPECT_LT(std::fabs(0.0 - transformed_vector_values.at(0)), kTolerance);
  EXPECT_LT(std::fabs(0.0 - transformed_vector_values.at(1)), kTolerance);
  EXPECT_LT(std::fabs(0.0 - transformed_vector_values.at(2)), kTolerance);
  EXPECT_LT(std::fabs(0.0 - transformed_vector_values.at(3)), kTolerance);
  EXPECT_LT(std::fabs(0.0 - transformed_vector_values.at(4)), kTolerance);
  EXPECT_LT(std::fabs(0.0 - transformed_vector_values.at(5)), kTolerance);
}

TEST_F(CatsxpAdsMappedTokensTransformationTest, EmptyMap) {
  // Arrange
  constexpr double kTolerance = 1e-6;

  constexpr char kTestString[] = "this is a simple test string";
  std::unique_ptr<Data> data = std::make_unique<TextData>(kTestString);

  int vector_dimension = 6;
  std::map<std::string, std::vector<uint16_t>> token_categories_mapping;

  std::optional<MappedTokensTransformation> to_mapped_tokens =
      BuildMappedTokensTransformation(vector_dimension,
                                      token_categories_mapping);
  ASSERT_TRUE(to_mapped_tokens);

  // Act
  data = to_mapped_tokens->Apply(data);
  ASSERT_EQ(DataType::kVector, data->GetType());
  const VectorData* const transformed_vector_data =
      static_cast<VectorData*>(data.get());

  const std::vector<float> transformed_vector_values =
      transformed_vector_data->GetDenseData();
  ASSERT_TRUE(transformed_vector_values.size() ==
              static_cast<size_t>(vector_dimension));

  // Assert
  EXPECT_LT(std::fabs(0.0 - transformed_vector_values.at(0)), kTolerance);
  EXPECT_LT(std::fabs(0.0 - transformed_vector_values.at(1)), kTolerance);
  EXPECT_LT(std::fabs(0.0 - transformed_vector_values.at(2)), kTolerance);
  EXPECT_LT(std::fabs(0.0 - transformed_vector_values.at(3)), kTolerance);
  EXPECT_LT(std::fabs(0.0 - transformed_vector_values.at(4)), kTolerance);
  EXPECT_LT(std::fabs(0.0 - transformed_vector_values.at(5)), kTolerance);
}

TEST_F(CatsxpAdsMappedTokensTransformationTest, NonTextData) {
  // Arrange
  VectorData vector_data({1.0, 2.0, 4.0, 0.03, 0.0});
  std::unique_ptr<Data> data = std::make_unique<VectorData>(vector_data);

  int vector_dimension = 6;
  std::map<std::string, std::vector<uint16_t>> token_categories_mapping = {
      {"is", {1}}, {"this", {5}}, {"test-string", {0, 3}}, {"simple", {1, 4}}};

  std::optional<MappedTokensTransformation> to_mapped_tokens =
      BuildMappedTokensTransformation(vector_dimension,
                                      token_categories_mapping);
  ASSERT_TRUE(to_mapped_tokens);

  // Act
  data = to_mapped_tokens->Apply(data);

  // Assert
  EXPECT_FALSE(data);
}

}  // namespace catsxp_ads::ml
