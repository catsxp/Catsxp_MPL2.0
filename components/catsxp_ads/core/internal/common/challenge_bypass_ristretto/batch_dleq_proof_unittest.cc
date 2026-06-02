/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/batch_dleq_proof.h"

#include <sstream>

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/blinded_token.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/public_key.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/signed_token.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/signing_key.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/blinded_token_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/challenge_bypass_ristretto_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/public_key_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/signed_token_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/signing_key_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/token_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/unblinded_token_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsBatchDLEQProofTest : public test::TestBase {};

TEST_F(CatsxpAdsBatchDLEQProofTest, FailToInitialize) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof;

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.has_value());
}

TEST_F(CatsxpAdsBatchDLEQProofTest, FailToInitializeWithEmptyBase64) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof("");

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.has_value());
}

TEST_F(CatsxpAdsBatchDLEQProofTest, FailToInitializeWithInvalidBase64) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.has_value());
}

TEST_F(CatsxpAdsBatchDLEQProofTest, FailToInitializeWithInvalidBlindedTokens) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(
      cbr::test::GetInvalidBlindedTokens(), cbr::test::GetSignedTokens(),
      cbr::test::GetSigningKey());

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.has_value());
}

TEST_F(CatsxpAdsBatchDLEQProofTest, FailToInitializeWithInvalidSignedTokens) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(
      cbr::test::GetBlindedTokens(), cbr::test::GetInvalidSignedTokens(),
      cbr::test::GetSigningKey());

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.has_value());
}

TEST_F(CatsxpAdsBatchDLEQProofTest, FailToInitializeWithInvalidSigningKey) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(cbr::test::GetBlindedTokens(),
                                             cbr::test::GetSignedTokens(),
                                             cbr::test::GetInvalidSigningKey());

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.has_value());
}

TEST_F(CatsxpAdsBatchDLEQProofTest, DecodeBase64) {
  // Act
  const cbr::BatchDLEQProof batch_dleq_proof =
      cbr::BatchDLEQProof::DecodeBase64(cbr::test::kBatchDLEQProofBase64);

  // Assert
  EXPECT_TRUE(batch_dleq_proof.has_value());
}

TEST_F(CatsxpAdsBatchDLEQProofTest, FailToDecodeEmptyBase64) {
  // Act
  const cbr::BatchDLEQProof batch_dleq_proof =
      cbr::BatchDLEQProof::DecodeBase64("");

  // Assert
  EXPECT_FALSE(batch_dleq_proof.has_value());
}

TEST_F(CatsxpAdsBatchDLEQProofTest, FailToDecodeInvalidBase64) {
  // Act
  const cbr::BatchDLEQProof batch_dleq_proof =
      cbr::BatchDLEQProof::DecodeBase64(cbr::test::kInvalidBase64);

  // Assert
  EXPECT_FALSE(batch_dleq_proof.has_value());
}

TEST_F(CatsxpAdsBatchDLEQProofTest, EncodeBase64) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::kBatchDLEQProofBase64, batch_dleq_proof.EncodeBase64());
}

TEST_F(CatsxpAdsBatchDLEQProofTest, FailToEncodeBase64WhenUninitialized) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof;

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.EncodeBase64());
}

TEST_F(CatsxpAdsBatchDLEQProofTest, Verify) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_TRUE(batch_dleq_proof.Verify(cbr::test::GetBlindedTokens(),
                                      cbr::test::GetSignedTokens(),
                                      cbr::test::GetPublicKey()));
}

TEST_F(CatsxpAdsBatchDLEQProofTest, FailToVerifyWhenUninitialized) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof;

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.Verify(cbr::test::GetBlindedTokens(),
                                       cbr::test::GetSignedTokens(),
                                       cbr::test::GetPublicKey()));
}

TEST_F(CatsxpAdsBatchDLEQProofTest, FailToVerifyWithInvalidBlindedTokens) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.Verify(cbr::test::GetInvalidBlindedTokens(),
                                       cbr::test::GetSignedTokens(),
                                       cbr::test::GetPublicKey()));
}

TEST_F(CatsxpAdsBatchDLEQProofTest, FailToVerifyWithInvalidSignedTokens) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.Verify(cbr::test::GetBlindedTokens(),
                                       cbr::test::GetInvalidSignedTokens(),
                                       cbr::test::GetPublicKey()));
}

TEST_F(CatsxpAdsBatchDLEQProofTest, FailToVerifyWithMismatchingPublicKey) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.Verify(cbr::test::GetBlindedTokens(),
                                       cbr::test::GetSignedTokens(),
                                       cbr::test::GetMismatchingPublicKey()));
}

TEST_F(CatsxpAdsBatchDLEQProofTest, FailToVerifyWithInvalidPublicKey) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.Verify(cbr::test::GetBlindedTokens(),
                                       cbr::test::GetSignedTokens(),
                                       cbr::test::GetInvalidPublicKey()));
}

TEST_F(CatsxpAdsBatchDLEQProofTest, VerifyAndUnblind) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::GetUnblindedTokens(),
            batch_dleq_proof.VerifyAndUnblind(
                cbr::test::GetTokens(), cbr::test::GetBlindedTokens(),
                cbr::test::GetSignedTokens(), cbr::test::GetPublicKey()));
}

TEST_F(CatsxpAdsBatchDLEQProofTest, FailToVerifyAndUnblindWhenUninitialized) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof;

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.VerifyAndUnblind(
      cbr::test::GetTokens(), cbr::test::GetBlindedTokens(),
      cbr::test::GetSignedTokens(), cbr::test::GetPublicKey()));
}

TEST_F(CatsxpAdsBatchDLEQProofTest, FailToVerifyAndUnblindWithInvalidTokens) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.VerifyAndUnblind(
      cbr::test::GetInvalidTokens(), cbr::test::GetBlindedTokens(),
      cbr::test::GetSignedTokens(), cbr::test::GetPublicKey()));
}

TEST_F(CatsxpAdsBatchDLEQProofTest,
       FailToVerifyAndUnblindWithInvalidBlindedTokens) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.VerifyAndUnblind(
      cbr::test::GetTokens(), cbr::test::GetInvalidBlindedTokens(),
      cbr::test::GetSignedTokens(), cbr::test::GetPublicKey()));
}

TEST_F(CatsxpAdsBatchDLEQProofTest,
       FailToVerifyAndUnblindWithInvalidSignedTokens) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.VerifyAndUnblind(
      cbr::test::GetTokens(), cbr::test::GetBlindedTokens(),
      cbr::test::GetInvalidSignedTokens(), cbr::test::GetPublicKey()));
}

TEST_F(CatsxpAdsBatchDLEQProofTest,
       FailToVerifyAndUnblindWithMismatchingPublicKey) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.VerifyAndUnblind(
      cbr::test::GetTokens(), cbr::test::GetBlindedTokens(),
      cbr::test::GetSignedTokens(), cbr::test::GetMismatchingPublicKey()));
}

TEST_F(CatsxpAdsBatchDLEQProofTest, FailToVerifyAndUnblindWithInvalidPublicKey) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.VerifyAndUnblind(
      cbr::test::GetTokens(), cbr::test::GetBlindedTokens(),
      cbr::test::GetSignedTokens(), cbr::test::GetInvalidPublicKey()));
}

TEST_F(CatsxpAdsBatchDLEQProofTest, IsEqual) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_EQ(batch_dleq_proof, batch_dleq_proof);
}

TEST_F(CatsxpAdsBatchDLEQProofTest, IsEqualWhenUninitialized) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof;

  // Act & Assert
  EXPECT_EQ(batch_dleq_proof, batch_dleq_proof);
}

TEST_F(CatsxpAdsBatchDLEQProofTest, IsEmptyBase64Equal) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof("");

  // Act & Assert
  EXPECT_EQ(batch_dleq_proof, batch_dleq_proof);
}

TEST_F(CatsxpAdsBatchDLEQProofTest, IsInvalidBase64Equal) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_EQ(batch_dleq_proof, batch_dleq_proof);
}

TEST_F(CatsxpAdsBatchDLEQProofTest, IsNotEqual) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  const cbr::BatchDLEQProof another_batch_dleq_proof(cbr::test::kInvalidBase64);
  EXPECT_NE(another_batch_dleq_proof, batch_dleq_proof);
}

TEST_F(CatsxpAdsBatchDLEQProofTest, OutputStream) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act
  std::stringstream ss;
  ss << batch_dleq_proof;

  // Assert
  EXPECT_EQ(cbr::test::kBatchDLEQProofBase64, ss.str());
}

TEST_F(CatsxpAdsBatchDLEQProofTest, OutputStreamWhenUninitialized) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof;

  // Act
  std::stringstream ss;
  ss << batch_dleq_proof;

  // Assert
  EXPECT_THAT(ss.str(), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
