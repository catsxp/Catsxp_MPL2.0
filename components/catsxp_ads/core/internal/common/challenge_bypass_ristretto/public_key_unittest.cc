/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/public_key.h"

#include <sstream>

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/challenge_bypass_ristretto_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsPublicKeyTest : public test::TestBase {};

TEST_F(CatsxpAdsPublicKeyTest, FailToInitialize) {
  // Arrange
  const cbr::PublicKey public_key;

  // Act & Assert
  EXPECT_FALSE(public_key.has_value());
}

TEST_F(CatsxpAdsPublicKeyTest, FailToInitializeWithEmptyBase64) {
  // Arrange
  const cbr::PublicKey public_key("");

  // Act & Assert
  EXPECT_FALSE(public_key.has_value());
}

TEST_F(CatsxpAdsPublicKeyTest, FailToInitializeWithInvalidBase64) {
  // Arrange
  const cbr::PublicKey public_key(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(public_key.has_value());
}

TEST_F(CatsxpAdsPublicKeyTest, DecodeBase64) {
  // Act
  const cbr::PublicKey public_key =
      cbr::PublicKey::DecodeBase64(cbr::test::kPublicKeyBase64);

  // Assert
  EXPECT_TRUE(public_key.has_value());
}

TEST_F(CatsxpAdsPublicKeyTest, FailToDecodeEmptyBase64) {
  // Act
  const cbr::PublicKey public_key = cbr::PublicKey::DecodeBase64("");

  // Assert
  EXPECT_FALSE(public_key.has_value());
}

TEST_F(CatsxpAdsPublicKeyTest, FailToDecodeInvalidBase64) {
  // Act
  const cbr::PublicKey public_key =
      cbr::PublicKey::DecodeBase64(cbr::test::kInvalidBase64);

  // Assert
  EXPECT_FALSE(public_key.has_value());
}

TEST_F(CatsxpAdsPublicKeyTest, EncodeBase64) {
  // Arrange
  const cbr::PublicKey public_key(cbr::test::kPublicKeyBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::kPublicKeyBase64, public_key.EncodeBase64());
}

TEST_F(CatsxpAdsPublicKeyTest, FailToEncodeBase64WhenUninitialized) {
  // Arrange
  const cbr::PublicKey public_key;

  // Act & Assert
  EXPECT_FALSE(public_key.EncodeBase64());
}

TEST_F(CatsxpAdsPublicKeyTest, IsEqual) {
  // Arrange
  const cbr::PublicKey public_key(cbr::test::kPublicKeyBase64);

  // Act & Assert
  EXPECT_EQ(public_key, public_key);
}

TEST_F(CatsxpAdsPublicKeyTest, IsEqualWhenUninitialized) {
  // Arrange
  const cbr::PublicKey public_key;

  // Act & Assert
  EXPECT_EQ(public_key, public_key);
}

TEST_F(CatsxpAdsPublicKeyTest, IsEmptyBase64Equal) {
  // Arrange
  const cbr::PublicKey public_key("");

  // Act & Assert
  EXPECT_EQ(public_key, public_key);
}

TEST_F(CatsxpAdsPublicKeyTest, IsInvalidBase64Equal) {
  // Arrange
  const cbr::PublicKey public_key(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_EQ(public_key, public_key);
}

TEST_F(CatsxpAdsPublicKeyTest, IsNotEqual) {
  // Arrange
  const cbr::PublicKey public_key(cbr::test::kPublicKeyBase64);

  // Act & Assert
  const cbr::PublicKey another_public_key(cbr::test::kInvalidBase64);
  EXPECT_NE(another_public_key, public_key);
}

TEST_F(CatsxpAdsPublicKeyTest, OutputStream) {
  // Arrange
  const cbr::PublicKey public_key(cbr::test::kPublicKeyBase64);

  // Act
  std::stringstream ss;
  ss << public_key;

  // Assert
  EXPECT_EQ(cbr::test::kPublicKeyBase64, ss.str());
}

TEST_F(CatsxpAdsPublicKeyTest, OutputStreamWhenUninitialized) {
  // Arrange
  const cbr::PublicKey public_key;

  // Act
  std::stringstream ss;
  ss << public_key;

  // Assert
  EXPECT_THAT(ss.str(), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
