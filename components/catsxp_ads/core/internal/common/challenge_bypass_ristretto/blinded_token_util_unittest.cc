/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/blinded_token_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/blinded_token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/blinded_token_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/token_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsBlindedTokenUtilTest, BlindTokens) {
  // Arrange
  const cbr::TokenList tokens = cbr::test::GetTokens();

  // Act
  const cbr::BlindedTokenList blinded_tokens = BlindTokens(tokens);

  // Assert
  EXPECT_EQ(cbr::test::GetBlindedTokens(), blinded_tokens);
}

TEST(CatsxpAdsBlindedTokenUtilTToUnblindedTokensest, BlindEmptyTokens) {
  // Act & Assert
  EXPECT_THAT(cbr::BlindTokens({}), ::testing::IsEmpty());
}

TEST(CatsxpAdsBlindedTokenUtilTest, BlindedTokensToRawBlindedTokens) {
  // Arrange
  const cbr::BlindedTokenList blinded_tokens = cbr::test::GetBlindedTokens();

  // Act
  const std::vector<challenge_bypass_ristretto::BlindedToken>
      raw_blinded_tokens = ToRawBlindedTokens(blinded_tokens);

  // Assert
  std::vector<challenge_bypass_ristretto::BlindedToken>
      expected_raw_blinded_tokens;
  expected_raw_blinded_tokens.reserve(blinded_tokens.size());
  for (const auto& blinded_token : blinded_tokens) {
    expected_raw_blinded_tokens.push_back(blinded_token.get());
  }
  EXPECT_EQ(expected_raw_blinded_tokens, raw_blinded_tokens);
}

TEST(CatsxpAdsBlindedTokenUtilTest, EmptyBlindedTokensToRawBlindedTokens) {
  // Act & Assert
  EXPECT_THAT(cbr::ToRawBlindedTokens({}), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
