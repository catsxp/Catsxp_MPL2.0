/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ml/transformation/lowercase_transformation.h"

#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/data/text_data.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/data/vector_data.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::ml {

class CatsxpAdsLowercaseTransformationTest : public test::TestBase {};

TEST_F(CatsxpAdsLowercaseTransformationTest, WrongInputDataTest) {
  // Arrange
  const std::unique_ptr<Data> vector_data =
      std::make_unique<VectorData>(std::vector<float>(1.0F));

  const LowercaseTransformation lowercase;

  // Act
  const std::unique_ptr<Data> output_data = lowercase.Apply(vector_data);

  // Assert
  EXPECT_FALSE(output_data.get());
}

TEST_F(CatsxpAdsLowercaseTransformationTest, LowercaseTest) {
  // Arrange
  constexpr char kUppercaseText[] = "LOWER CASE";
  constexpr char kLowercaseText[] = "lower case";
  const std::unique_ptr<Data> uppercase_data =
      std::make_unique<TextData>(kUppercaseText);

  const LowercaseTransformation lowercase;

  // Act
  const std::unique_ptr<Data> lowercase_data = lowercase.Apply(uppercase_data);

  ASSERT_EQ(DataType::kText, lowercase_data->GetType());
  const TextData* const lowercase_text_data =
      static_cast<TextData*>(lowercase_data.get());

  // Assert
  EXPECT_EQ(kLowercaseText, lowercase_text_data->GetText());
}

}  // namespace catsxp_ads::ml
