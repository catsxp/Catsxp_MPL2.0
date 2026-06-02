/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ml/data/text_data.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::ml {

class CatsxpAdsTextDataTest : public test::TestBase {};

TEST_F(CatsxpAdsTextDataTest, TextDataInitialization) {
  // Arrange
  const std::string text = "The quick brown fox jumps over the lazy dog";

  // Act
  const TextData text_data(text);

  // Assert
  EXPECT_EQ(text, text_data.GetText());
}

}  // namespace catsxp_ads::ml
