/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token.h"

#include <sstream>

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/challenge_bypass_ristretto_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsTokenTest : public test::TestBase {};

TEST_F(CatsxpAdsTokenTest, Random) {
  // Arrange
  const cbr::Token token;

  // Act & Assert
  EXPECT_TRUE(token.has_value());
}

TEST_F(CatsxpAdsTokenTest, FailToInitializeWithEmptyBase64) {
  // Arrange
  const cbr::Token token("");

  // Act & Assert
  EXPECT_FALSE(token.has_value());
}

TEST_F(CatsxpAdsTokenTest, FailToInitializeWithInvalidBase64) {
  // Arrange
  const cbr::Token token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(token.has_value());
}

TEST_F(CatsxpAdsTokenTest, DecodeBase64) {
  // Act
  const cbr::Token token = cbr::Token::DecodeBase64(cbr::test::kTokenBase64);

  // Assert
  EXPECT_TRUE(token.has_value());
}

TEST_F(CatsxpAdsTokenTest, FailToDecodeEmptyBase64) {
  // Act
  const cbr::Token token = cbr::Token::DecodeBase64("");

  // Assert
  EXPECT_FALSE(token.has_value());
}

TEST_F(CatsxpAdsTokenTest, FailToDecodeInvalidBase64) {
  // Act
  const cbr::Token token = cbr::Token::DecodeBase64(cbr::test::kInvalidBase64);

  // Assert
  EXPECT_FALSE(token.has_value());
}

TEST_F(CatsxpAdsTokenTest, EncodeBase64) {
  // Arrange
  const cbr::Token token(cbr::test::kTokenBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::kTokenBase64, token.EncodeBase64());
}

TEST_F(CatsxpAdsTokenTest, EncodeRandomBase64) {
  // Arrange
  const cbr::Token token;

  // Act & Assert
  EXPECT_TRUE(token.EncodeBase64());
}

TEST_F(CatsxpAdsTokenTest, IsEqual) {
  // Arrange
  const cbr::Token token;

  // Act & Assert
  EXPECT_EQ(token, token);
}

TEST_F(CatsxpAdsTokenTest, IsEmptyBase64Equal) {
  // Arrange
  const cbr::Token token("");

  // Act & Assert
  EXPECT_EQ(token, token);
}

TEST_F(CatsxpAdsTokenTest, IsInvalidBase64Equal) {
  // Arrange
  const cbr::Token token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_EQ(token, token);
}

TEST_F(CatsxpAdsTokenTest, IsNotEqual) {
  // Arrange
  const cbr::Token token;

  // Act & Assert
  const cbr::Token another_token;
  EXPECT_NE(another_token, token);
}

TEST_F(CatsxpAdsTokenTest, OutputStream) {
  // Arrange
  const cbr::Token token(cbr::test::kTokenBase64);

  // Act
  std::stringstream ss;
  ss << token;

  // Assert
  EXPECT_EQ(cbr::test::kTokenBase64, ss.str());
}

}  // namespace catsxp_ads
