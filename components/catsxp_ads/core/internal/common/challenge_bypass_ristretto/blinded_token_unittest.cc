/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/blinded_token.h"

#include <sstream>

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/challenge_bypass_ristretto_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsBlindedTokenTest : public test::TestBase {};

TEST_F(CatsxpAdsBlindedTokenTest, FailToInitialize) {
  // Arrange
  const cbr::BlindedToken blinded_token;

  // Act & Assert
  EXPECT_FALSE(blinded_token.has_value());
}

TEST_F(CatsxpAdsBlindedTokenTest, FailToInitializeWithEmptyBase64) {
  // Arrange
  const cbr::BlindedToken blinded_token("");

  // Act & Assert
  EXPECT_FALSE(blinded_token.has_value());
}

TEST_F(CatsxpAdsBlindedTokenTest, FailToInitializeWithInvalidBase64) {
  // Arrange
  const cbr::BlindedToken blinded_token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(blinded_token.has_value());
}

TEST_F(CatsxpAdsBlindedTokenTest, DecodeBase64) {
  // Act
  const cbr::BlindedToken blinded_token =
      cbr::BlindedToken::DecodeBase64(cbr::test::kBlindedTokenBase64);

  // Assert
  EXPECT_TRUE(blinded_token.has_value());
}

TEST_F(CatsxpAdsBlindedTokenTest, FailToDecodeEmptyBase64) {
  // Act
  const cbr::BlindedToken blinded_token = cbr::BlindedToken::DecodeBase64("");

  // Assert
  EXPECT_FALSE(blinded_token.has_value());
}

TEST_F(CatsxpAdsBlindedTokenTest, FailToDecodeInvalidBase64) {
  // Act
  const cbr::BlindedToken blinded_token =
      cbr::BlindedToken::DecodeBase64(cbr::test::kInvalidBase64);

  // Assert
  EXPECT_FALSE(blinded_token.has_value());
}

TEST_F(CatsxpAdsBlindedTokenTest, EncodeBase64) {
  // Arrange
  const cbr::BlindedToken blinded_token(cbr::test::kBlindedTokenBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::kBlindedTokenBase64, blinded_token.EncodeBase64());
}

TEST_F(CatsxpAdsBlindedTokenTest, FailToEncodeBase64WhenUninitialized) {
  // Arrange
  const cbr::BlindedToken blinded_token;

  // Act & Assert
  EXPECT_FALSE(blinded_token.EncodeBase64());
}

TEST_F(CatsxpAdsBlindedTokenTest, IsEqual) {
  // Arrange
  const cbr::BlindedToken blinded_token(cbr::test::kBlindedTokenBase64);

  // Act & Assert
  EXPECT_EQ(blinded_token, blinded_token);
}

TEST_F(CatsxpAdsBlindedTokenTest, IsEqualWhenUninitialized) {
  // Arrange
  const cbr::BlindedToken blinded_token;

  // Act & Assert
  EXPECT_EQ(blinded_token, blinded_token);
}

TEST_F(CatsxpAdsBlindedTokenTest, IsEmptyBase64Equal) {
  // Arrange
  const cbr::BlindedToken blinded_token("");

  // Act & Assert
  EXPECT_EQ(blinded_token, blinded_token);
}

TEST_F(CatsxpAdsBlindedTokenTest, IsInvalidBase64Equal) {
  // Arrange
  const cbr::BlindedToken blinded_token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_EQ(blinded_token, blinded_token);
}

TEST_F(CatsxpAdsBlindedTokenTest, IsNotEqual) {
  // Act & Assert
  EXPECT_NE(cbr::BlindedToken(cbr::test::kBlindedTokenBase64),
            cbr::BlindedToken(cbr::test::kInvalidBase64));
}

TEST_F(CatsxpAdsBlindedTokenTest, OutputStream) {
  // Arrange
  const cbr::BlindedToken blinded_token(cbr::test::kBlindedTokenBase64);

  // Act
  std::stringstream ss;
  ss << blinded_token;

  // Assert
  EXPECT_EQ(cbr::test::kBlindedTokenBase64, ss.str());
}

TEST_F(CatsxpAdsBlindedTokenTest, OutputStreamWhenUninitialized) {
  // Arrange
  const cbr::BlindedToken blinded_token;

  // Act
  std::stringstream ss;
  ss << blinded_token;

  // Assert
  EXPECT_THAT(ss.str(), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
