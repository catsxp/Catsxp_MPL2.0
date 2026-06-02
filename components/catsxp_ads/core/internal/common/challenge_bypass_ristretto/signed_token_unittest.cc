/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/signed_token.h"

#include <sstream>

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/challenge_bypass_ristretto_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsSignedTokenTest : public test::TestBase {};

TEST_F(CatsxpAdsSignedTokenTest, FailToInitialize) {
  // Arrange
  const cbr::SignedToken signed_token;

  // Act & Assert
  EXPECT_FALSE(signed_token.has_value());
}

TEST_F(CatsxpAdsSignedTokenTest, FailToInitializeWithEmptyBase64) {
  // Arrange
  const cbr::SignedToken signed_token("");

  // Act & Assert
  EXPECT_FALSE(signed_token.has_value());
}

TEST_F(CatsxpAdsSignedTokenTest, FailToInitializeWithInvalidBase64) {
  // Arrange
  const cbr::SignedToken signed_token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(signed_token.has_value());
}

TEST_F(CatsxpAdsSignedTokenTest, DecodeBase64) {
  // Act
  const cbr::SignedToken signed_token =
      cbr::SignedToken::DecodeBase64(cbr::test::kSignedTokenBase64);

  // Assert
  EXPECT_TRUE(signed_token.has_value());
}

TEST_F(CatsxpAdsSignedTokenTest, FailToDecodeEmptyBase64) {
  // Act
  const cbr::SignedToken signed_token = cbr::SignedToken::DecodeBase64("");

  // Assert
  EXPECT_FALSE(signed_token.has_value());
}

TEST_F(CatsxpAdsSignedTokenTest, FailToDecodeInvalidBase64) {
  // Act
  const cbr::SignedToken signed_token =
      cbr::SignedToken::DecodeBase64(cbr::test::kInvalidBase64);

  // Assert
  EXPECT_FALSE(signed_token.has_value());
}

TEST_F(CatsxpAdsSignedTokenTest, EncodeBase64) {
  // Arrange
  const cbr::SignedToken signed_token(cbr::test::kSignedTokenBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::kSignedTokenBase64, signed_token.EncodeBase64());
}

TEST_F(CatsxpAdsSignedTokenTest, FailToEncodeBase64WhenUninitialized) {
  // Arrange
  const cbr::SignedToken signed_token;

  // Act & Assert
  EXPECT_FALSE(signed_token.EncodeBase64());
}

TEST_F(CatsxpAdsSignedTokenTest, IsEqual) {
  // Arrange
  const cbr::SignedToken signed_token(cbr::test::kSignedTokenBase64);

  // Act & Assert
  EXPECT_EQ(signed_token, signed_token);
}

TEST_F(CatsxpAdsSignedTokenTest, IsEqualWhenUninitialized) {
  // Arrange
  const cbr::SignedToken signed_token;

  // Act & Assert
  EXPECT_EQ(signed_token, signed_token);
}

TEST_F(CatsxpAdsSignedTokenTest, IsEmptyBase64Equal) {
  // Arrange
  const cbr::SignedToken signed_token("");

  // Act & Assert
  EXPECT_EQ(signed_token, signed_token);
}

TEST_F(CatsxpAdsSignedTokenTest, IsInvalidBase64Equal) {
  // Arrange
  const cbr::SignedToken signed_token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_EQ(signed_token, signed_token);
}

TEST_F(CatsxpAdsSignedTokenTest, IsNotEqual) {
  // Arrange
  const cbr::SignedToken signed_token(cbr::test::kSignedTokenBase64);

  // Act & Assert
  const cbr::SignedToken another_signed_token(cbr::test::kInvalidBase64);
  EXPECT_NE(another_signed_token, signed_token);
}

TEST_F(CatsxpAdsSignedTokenTest, OutputStream) {
  // Arrange
  const cbr::SignedToken signed_token(cbr::test::kSignedTokenBase64);

  // Act
  std::stringstream ss;
  ss << signed_token;

  // Assert
  EXPECT_EQ(cbr::test::kSignedTokenBase64, ss.str());
}

TEST_F(CatsxpAdsSignedTokenTest, OutputStreamWhenUninitialized) {
  // Arrange
  const cbr::SignedToken signed_token;

  // Act
  std::stringstream ss;
  ss << signed_token;

  // Assert
  EXPECT_THAT(ss.str(), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
