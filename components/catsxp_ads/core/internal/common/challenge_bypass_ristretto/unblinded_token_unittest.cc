/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/challenge_bypass_ristretto_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/token_preimage_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token_preimage.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/verification_key.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsUnblindedTokenTest : public test::TestBase {};

TEST_F(CatsxpAdsUnblindedTokenTest, FailToInitialize) {
  // Arrange
  const cbr::UnblindedToken unblinded_token;

  // Act & Assert
  EXPECT_FALSE(unblinded_token.has_value());
}

TEST_F(CatsxpAdsUnblindedTokenTest, FailToInitializeWithEmptyBase64) {
  // Arrange
  const cbr::UnblindedToken unblinded_token("");

  // Act & Assert
  EXPECT_FALSE(unblinded_token.has_value());
}

TEST_F(CatsxpAdsUnblindedTokenTest, FailToInitializeWithInvalidBase64) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(unblinded_token.has_value());
}

TEST_F(CatsxpAdsUnblindedTokenTest, DecodeBase64) {
  // Act
  const cbr::UnblindedToken unblinded_token =
      cbr::UnblindedToken::DecodeBase64(cbr::test::kUnblindedTokenBase64);

  // Assert
  EXPECT_TRUE(unblinded_token.has_value());
}

TEST_F(CatsxpAdsUnblindedTokenTest, FailToDecodeEmptyBase64) {
  // Act
  const cbr::UnblindedToken unblinded_token =
      cbr::UnblindedToken::DecodeBase64("");

  // Assert
  EXPECT_FALSE(unblinded_token.has_value());
}

TEST_F(CatsxpAdsUnblindedTokenTest, FailToDecodeInvalidBase64) {
  // Act
  const cbr::UnblindedToken unblinded_token =
      cbr::UnblindedToken::DecodeBase64(cbr::test::kInvalidBase64);

  // Assert
  EXPECT_FALSE(unblinded_token.has_value());
}

TEST_F(CatsxpAdsUnblindedTokenTest, EncodeBase64) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kUnblindedTokenBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::kUnblindedTokenBase64, unblinded_token.EncodeBase64());
}

TEST_F(CatsxpAdsUnblindedTokenTest, FailToEncodeBase64WhenUninitialized) {
  // Arrange
  const cbr::UnblindedToken unblinded_token;

  // Act & Assert
  EXPECT_FALSE(unblinded_token.EncodeBase64());
}

TEST_F(CatsxpAdsUnblindedTokenTest, IsEqual) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kUnblindedTokenBase64);

  // Act & Assert
  EXPECT_EQ(unblinded_token, unblinded_token);
}

TEST_F(CatsxpAdsUnblindedTokenTest, IsEqualWhenUninitialized) {
  // Arrange
  const cbr::UnblindedToken unblinded_token;

  // Act & Assert
  EXPECT_EQ(unblinded_token, unblinded_token);
}

TEST_F(CatsxpAdsUnblindedTokenTest, IsEmptyBase64Equal) {
  // Arrange
  const cbr::UnblindedToken unblinded_token("");

  // Act & Assert
  EXPECT_EQ(unblinded_token, unblinded_token);
}

TEST_F(CatsxpAdsUnblindedTokenTest, IsInvalidBase64Equal) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_EQ(unblinded_token, unblinded_token);
}

TEST_F(CatsxpAdsUnblindedTokenTest, IsNotEqual) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kUnblindedTokenBase64);

  // Act & Assert
  const cbr::UnblindedToken another_blinded_token(cbr::test::kInvalidBase64);
  EXPECT_NE(another_blinded_token, unblinded_token);
}

TEST_F(CatsxpAdsUnblindedTokenTest, OutputStream) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kUnblindedTokenBase64);

  // Act
  std::stringstream ss;
  ss << unblinded_token;

  // Assert
  EXPECT_EQ(cbr::test::kUnblindedTokenBase64, ss.str());
}

TEST_F(CatsxpAdsUnblindedTokenTest, OutputStreamWhenUninitialized) {
  // Arrange
  const cbr::UnblindedToken unblinded_token;

  // Act
  std::stringstream ss;
  ss << unblinded_token;

  // Assert
  EXPECT_THAT(ss.str(), ::testing::IsEmpty());
}

TEST_F(CatsxpAdsUnblindedTokenTest, DeriveVerificationKey) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kUnblindedTokenBase64);

  // Act & Assert
  EXPECT_TRUE(unblinded_token.DeriveVerificationKey());
}

TEST_F(CatsxpAdsUnblindedTokenTest,
       FailToDeriveVerificationKeyWhenUninitialized) {
  // Arrange
  const cbr::UnblindedToken unblinded_token;

  // Act & Assert
  EXPECT_FALSE(unblinded_token.DeriveVerificationKey());
}

TEST_F(CatsxpAdsUnblindedTokenTest,
       FailToDeriveVerificationKeyWithInvalidUnblindedToken) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(unblinded_token.DeriveVerificationKey());
}

TEST_F(CatsxpAdsUnblindedTokenTest, GetTokenPreimage) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kUnblindedTokenBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::GetTokenPreimage(), unblinded_token.GetTokenPreimage());
}

TEST_F(CatsxpAdsUnblindedTokenTest, FailToGetTokenPreimageWhenUninitialized) {
  // Arrange
  const cbr::UnblindedToken unblinded_token;

  // Act & Assert
  EXPECT_FALSE(unblinded_token.GetTokenPreimage());
}

TEST_F(CatsxpAdsUnblindedTokenTest,
       FailToGetTokenPreimageWithInvalidUnblindedToken) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(unblinded_token.GetTokenPreimage());
}

}  // namespace catsxp_ads
