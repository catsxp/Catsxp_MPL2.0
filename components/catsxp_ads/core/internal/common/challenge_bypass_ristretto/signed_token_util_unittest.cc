/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/signed_token_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/signed_token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/signed_token_test_util.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsSignedTokenUtilTest, SignedTokensToRawSignedTokens) {
  // Arrange
  const cbr::SignedTokenList signed_tokens = cbr::test::GetSignedTokens();

  // Act
  const std::vector<challenge_bypass_ristretto::SignedToken> raw_signed_tokens =
      ToRawSignedTokens(signed_tokens);

  // Assert
  std::vector<challenge_bypass_ristretto::SignedToken>
      expected_raw_signed_tokens;
  expected_raw_signed_tokens.reserve(signed_tokens.size());
  for (const auto& signed_token : signed_tokens) {
    expected_raw_signed_tokens.push_back(signed_token.get());
  }
  EXPECT_EQ(expected_raw_signed_tokens, raw_signed_tokens);
}

TEST(CatsxpAdsSignedTokenUtilTest, EmptySignedTokensToRawSignedTokens) {
  // Act
  const std::vector<challenge_bypass_ristretto::SignedToken> raw_signed_tokens =
      cbr::ToRawSignedTokens({});

  // Assert
  EXPECT_THAT(raw_signed_tokens, ::testing::IsEmpty());
}

}  // namespace catsxp_ads
