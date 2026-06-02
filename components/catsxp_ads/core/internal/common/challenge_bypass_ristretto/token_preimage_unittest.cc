/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token_preimage.h"

#include <sstream>

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/challenge_bypass_ristretto_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsTokenPreimageTest : public test::TestBase {};

TEST_F(CatsxpAdsTokenPreimageTest, FailToInitialize) {
  // Arrange
  const cbr::TokenPreimage token_preimage;

  // Act & Assert
  EXPECT_FALSE(token_preimage.has_value());
}

TEST_F(CatsxpAdsTokenPreimageTest, FailToInitializeWithEmptyBase64) {
  // Arrange
  const cbr::TokenPreimage token_preimage("");

  // Act & Assert
  EXPECT_FALSE(token_preimage.has_value());
}

TEST_F(CatsxpAdsTokenPreimageTest, FailToInitializeWithInvalidBase64) {
  // Arrange
  const cbr::TokenPreimage token_preimage(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(token_preimage.has_value());
}

TEST_F(CatsxpAdsTokenPreimageTest, DecodeBase64) {
  // Act
  const cbr::TokenPreimage token_preimage =
      cbr::TokenPreimage::DecodeBase64(cbr::test::kTokenPreimageBase64);

  // Assert
  EXPECT_TRUE(token_preimage.has_value());
}

TEST_F(CatsxpAdsTokenPreimageTest, FailToDecodeEmptyBase64) {
  // Act
  const cbr::TokenPreimage token_preimage =
      cbr::TokenPreimage::DecodeBase64("");

  // Assert
  EXPECT_FALSE(token_preimage.has_value());
}

TEST_F(CatsxpAdsTokenPreimageTest, FailToDecodeInvalidBase64) {
  // Act
  const cbr::TokenPreimage token_preimage =
      cbr::TokenPreimage::DecodeBase64(cbr::test::kInvalidBase64);

  // Assert
  EXPECT_FALSE(token_preimage.has_value());
}

TEST_F(CatsxpAdsTokenPreimageTest, EncodeBase64) {
  // Arrange
  const cbr::TokenPreimage token_preimage(cbr::test::kTokenPreimageBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::kTokenPreimageBase64, token_preimage.EncodeBase64());
}

TEST_F(CatsxpAdsTokenPreimageTest, FailToEncodeBase64WhenUninitialized) {
  // Arrange
  const cbr::TokenPreimage token_preimage;

  // Act & Assert
  EXPECT_FALSE(token_preimage.EncodeBase64());
}

TEST_F(CatsxpAdsTokenPreimageTest, IsEqual) {
  // Arrange
  const cbr::TokenPreimage token_preimage(cbr::test::kTokenPreimageBase64);

  // Act & Assert
  EXPECT_EQ(token_preimage, token_preimage);
}

TEST_F(CatsxpAdsTokenPreimageTest, IsEqualWhenUninitialized) {
  // Arrange
  const cbr::TokenPreimage token_preimage;

  // Act & Assert
  EXPECT_EQ(token_preimage, token_preimage);
}

TEST_F(CatsxpAdsTokenPreimageTest, IsEmptyBase64Equal) {
  // Arrange
  const cbr::TokenPreimage token_preimage("");

  // Act & Assert
  EXPECT_EQ(token_preimage, token_preimage);
}

TEST_F(CatsxpAdsTokenPreimageTest, IsInvalidBase64Equal) {
  // Arrange
  const cbr::TokenPreimage token_preimage(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_EQ(token_preimage, token_preimage);
}

TEST_F(CatsxpAdsTokenPreimageTest, IsNotEqual) {
  // Arrange
  const cbr::TokenPreimage token_preimage(cbr::test::kTokenPreimageBase64);

  // Act & Assert
  const cbr::TokenPreimage another_token_preimage(cbr::test::kInvalidBase64);
  EXPECT_NE(another_token_preimage, token_preimage);
}

TEST_F(CatsxpAdsTokenPreimageTest, OutputStream) {
  // Arrange
  const cbr::TokenPreimage token_preimage(cbr::test::kTokenPreimageBase64);

  // Act
  std::stringstream ss;
  ss << token_preimage;

  // Assert
  EXPECT_EQ(cbr::test::kTokenPreimageBase64, ss.str());
}

TEST_F(CatsxpAdsTokenPreimageTest, OutputStreamWhenUninitialized) {
  // Arrange
  const cbr::TokenPreimage token_preimage;

  // Act
  std::stringstream ss;
  ss << token_preimage;

  // Assert
  EXPECT_THAT(ss.str(), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
