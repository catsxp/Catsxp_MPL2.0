/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/verification_signature.h"

#include <sstream>

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/challenge_bypass_ristretto_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsVerificationSignatureTest : public test::TestBase {};

TEST_F(CatsxpAdsVerificationSignatureTest, FailToInitialize) {
  // Arrange
  const cbr::VerificationSignature verification_signature;

  // Act & Assert
  EXPECT_FALSE(verification_signature.has_value());
}

TEST_F(CatsxpAdsVerificationSignatureTest, FailToInitializeWithEmptyBase64) {
  // Arrange
  const cbr::VerificationSignature verification_signature("");

  // Act & Assert
  EXPECT_FALSE(verification_signature.has_value());
}

TEST_F(CatsxpAdsVerificationSignatureTest, FailToInitializeWithInvalidBase64) {
  // Arrange
  const cbr::VerificationSignature verification_signature(
      cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(verification_signature.has_value());
}

TEST_F(CatsxpAdsVerificationSignatureTest, DecodeBase64) {
  // Act
  const cbr::VerificationSignature verification_signature =
      cbr::VerificationSignature::DecodeBase64(
          cbr::test::kVerificationSignatureBase64);

  // Assert
  EXPECT_TRUE(verification_signature.has_value());
}

TEST_F(CatsxpAdsVerificationSignatureTest, FailToDecodeEmptyBase64) {
  // Act
  const cbr::VerificationSignature verification_signature =
      cbr::VerificationSignature::DecodeBase64("");

  // Assert
  EXPECT_FALSE(verification_signature.has_value());
}

TEST_F(CatsxpAdsVerificationSignatureTest, FailToDecodeInvalidBase64) {
  // Act
  const cbr::VerificationSignature verification_signature =
      cbr::VerificationSignature::DecodeBase64(cbr::test::kInvalidBase64);

  // Assert
  EXPECT_FALSE(verification_signature.has_value());
}

TEST_F(CatsxpAdsVerificationSignatureTest, EncodeBase64) {
  // Arrange
  const cbr::VerificationSignature verification_signature(
      cbr::test::kVerificationSignatureBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::kVerificationSignatureBase64,
            verification_signature.EncodeBase64());
}

TEST_F(CatsxpAdsVerificationSignatureTest, FailToEncodeBase64WhenUninitialized) {
  // Arrange
  const cbr::VerificationSignature verification_signature;

  // Act & Assert
  EXPECT_FALSE(verification_signature.EncodeBase64());
}

TEST_F(CatsxpAdsVerificationSignatureTest, IsEqual) {
  // Arrange
  const cbr::VerificationSignature verification_signature(
      cbr::test::kVerificationSignatureBase64);

  // Act & Assert
  EXPECT_EQ(verification_signature, verification_signature);
}

TEST_F(CatsxpAdsVerificationSignatureTest, IsEqualWhenUninitialized) {
  // Arrange
  const cbr::VerificationSignature verification_signature;

  // Act & Assert
  EXPECT_EQ(verification_signature, verification_signature);
}

TEST_F(CatsxpAdsVerificationSignatureTest, IsEmptyBase64Equal) {
  // Arrange
  const cbr::VerificationSignature verification_signature("");

  // Act & Assert
  EXPECT_EQ(verification_signature, verification_signature);
}

TEST_F(CatsxpAdsVerificationSignatureTest, IsInvalidBase64Equal) {
  // Arrange
  const cbr::VerificationSignature verification_signature(
      cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_EQ(verification_signature, verification_signature);
}

TEST_F(CatsxpAdsVerificationSignatureTest, IsNotEqual) {
  // Arrange
  const cbr::VerificationSignature verification_signature(
      cbr::test::kVerificationSignatureBase64);

  // Act & Assert
  const cbr::VerificationSignature another_verification_signature(
      cbr::test::kInvalidBase64);
  EXPECT_NE(another_verification_signature, verification_signature);
}

TEST_F(CatsxpAdsVerificationSignatureTest, OutputStream) {
  // Arrange
  const cbr::VerificationSignature verification_signature(
      cbr::test::kVerificationSignatureBase64);

  // Act
  std::stringstream ss;
  ss << verification_signature;

  // Assert
  EXPECT_EQ(cbr::test::kVerificationSignatureBase64, ss.str());
}

TEST_F(CatsxpAdsVerificationSignatureTest, OutputStreamWhenUninitialized) {
  // Arrange
  const cbr::VerificationSignature verification_signature;

  // Act
  std::stringstream ss;
  ss << verification_signature;

  // Assert
  EXPECT_THAT(ss.str(), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
