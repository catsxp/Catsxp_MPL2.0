/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/token_generator.h"

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsTokenGeneratorTest, Generate) {
  // Arrange
  const TokenGenerator token_generator;

  // Act
  const cbr::TokenList tokens = token_generator.Generate(5);

  // Assert
  EXPECT_THAT(tokens, ::testing::SizeIs(5));
}

TEST(CatsxpAdsTokenGeneratorTest, GenerateZero) {
  // Arrange
  const TokenGenerator token_generator;

  // Act
  const cbr::TokenList tokens = token_generator.Generate(0);

  // Assert
  EXPECT_THAT(tokens, ::testing::IsEmpty());
}

}  // namespace catsxp_ads
