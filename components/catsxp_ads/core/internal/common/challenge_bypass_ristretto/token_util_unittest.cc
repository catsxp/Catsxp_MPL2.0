/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/token_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsTokenUtilTest, TokensToRawTokens) {
  // Arrange
  const cbr::TokenList tokens = cbr::test::GetTokens();

  // Act
  const std::vector<challenge_bypass_ristretto::Token> raw_tokens =
      ToRawTokens(tokens);

  // Assert
  std::vector<challenge_bypass_ristretto::Token> expected_raw_tokens;
  expected_raw_tokens.reserve(tokens.size());
  for (const auto& token : tokens) {
    expected_raw_tokens.push_back(token.get());
  }
  EXPECT_EQ(expected_raw_tokens, raw_tokens);
}

TEST(CatsxpAdsTokenUtilTest, EmptyTokensToRawTokens) {
  // Act
  const std::vector<challenge_bypass_ristretto::Token> raw_tokens =
      cbr::ToRawTokens({});

  // Assert
  EXPECT_THAT(raw_tokens, ::testing::IsEmpty());
}

}  // namespace catsxp_ads
