/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/signing_key.h"

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/blinded_token.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/public_key.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/signed_token.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/blinded_token_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/challenge_bypass_ristretto_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/signed_token_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/token_preimage_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/unblinded_token_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token_preimage.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsSigningKeyTest : public test::TestBase {};

TEST_F(CatsxpAdsSigningKeyTest, FailToInitializeWithEmptyBase64) {
  // Arrange
  const cbr::SigningKey signing_key("");

  // Act & Assert
  EXPECT_FALSE(signing_key.has_value());
}

TEST_F(CatsxpAdsSigningKeyTest, FailToInitializeWithInvalidBase64) {
  // Arrange
  const cbr::SigningKey signing_key(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(signing_key.has_value());
}

TEST_F(CatsxpAdsSigningKeyTest, DecodeBase64) {
  // Act
  const cbr::SigningKey signing_key =
      cbr::SigningKey::DecodeBase64(cbr::test::kSigningKeyBase64);

  // Assert
  EXPECT_TRUE(signing_key.has_value());
}

TEST_F(CatsxpAdsSigningKeyTest, FailToDecodeEmptyBase64) {
  // Act
  const cbr::SigningKey signing_key = cbr::SigningKey::DecodeBase64("");

  // Assert
  EXPECT_FALSE(signing_key.has_value());
}

TEST_F(CatsxpAdsSigningKeyTest, FailToDecodeInvalidBase64) {
  // Act
  const cbr::SigningKey signing_key =
      cbr::SigningKey::DecodeBase64(cbr::test::kInvalidBase64);

  // Assert
  EXPECT_FALSE(signing_key.has_value());
}

TEST_F(CatsxpAdsSigningKeyTest, EncodeBase64) {
  // Arrange
  const cbr::SigningKey signing_key(cbr::test::kSigningKeyBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::kSigningKeyBase64, signing_key.EncodeBase64());
}

TEST_F(CatsxpAdsSigningKeyTest, Sign) {
  // Arrange
  const cbr::SigningKey signing_key(cbr::test::kSigningKeyBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::GetSignedToken(),
            signing_key.Sign(cbr::test::GetBlindedToken()));
}

TEST_F(CatsxpAdsSigningKeyTest, FailToSignWithInvalidBlindedToken) {
  // Arrange
  const cbr::SigningKey signing_key(cbr::test::kSigningKeyBase64);

  // Act & Assert
  EXPECT_FALSE(signing_key.Sign(cbr::test::GetInvalidBlindedToken()));
}

TEST_F(CatsxpAdsSigningKeyTest, RederiveUnblindedToken) {
  // Arrange
  cbr::SigningKey signing_key(cbr::test::kSigningKeyBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::GetUnblindedToken(),
            signing_key.RederiveUnblindedToken(cbr::test::GetTokenPreimage()));
}

TEST_F(CatsxpAdsSigningKeyTest,
       FailToRederiveUnblindedTokenWithInvalidTokenPreimage) {
  // Arrange
  cbr::SigningKey signing_key(cbr::test::kSigningKeyBase64);

  // Act & Assert
  EXPECT_FALSE(
      signing_key.RederiveUnblindedToken(cbr::test::GetInvalidTokenPreimage()));
}

TEST_F(CatsxpAdsSigningKeyTest, GetPublicKey) {
  // Arrange
  cbr::SigningKey signing_key(cbr::test::kSigningKeyBase64);

  // Act & Assert
  EXPECT_EQ(cbr::PublicKey(cbr::test::kPublicKeyBase64),
            signing_key.GetPublicKey());
}

TEST_F(CatsxpAdsSigningKeyTest, IsEqual) {
  // Arrange
  const cbr::SigningKey signing_key;

  // Act & Assert
  EXPECT_EQ(signing_key, signing_key);
}

TEST_F(CatsxpAdsSigningKeyTest, IsEmptyBase64Equal) {
  // Arrange
  const cbr::SigningKey signing_key("");

  // Act & Assert
  EXPECT_EQ(signing_key, signing_key);
}

TEST_F(CatsxpAdsSigningKeyTest, IsInvalidBase64Equal) {
  // Arrange
  const cbr::SigningKey signing_key(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_EQ(signing_key, signing_key);
}

TEST_F(CatsxpAdsSigningKeyTest, IsNotEqual) {
  // Arrange
  const cbr::SigningKey signing_key;

  // Act & Assert
  const cbr::SigningKey another_signing_key;
  EXPECT_NE(another_signing_key, signing_key);
}

TEST_F(CatsxpAdsSigningKeyTest, OutputStream) {
  // Arrange
  const cbr::SigningKey signing_key(cbr::test::kSigningKeyBase64);

  // Act
  std::stringstream ss;
  ss << signing_key;

  // Assert
  EXPECT_EQ(cbr::test::kSigningKeyBase64, ss.str());
}

}  // namespace catsxp_ads
