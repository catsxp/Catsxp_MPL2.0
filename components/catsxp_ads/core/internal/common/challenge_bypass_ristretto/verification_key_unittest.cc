/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/verification_key.h"

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/verification_key_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/verification_signature_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/verification_signature.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {
constexpr char kMessage[] = "The quick brown fox jumps over the lazy dog";
}  // namespace

class CatsxpAdsVerificationKeyTest : public test::TestBase {};

TEST_F(CatsxpAdsVerificationKeyTest, Sign) {
  // Arrange
  cbr::VerificationKey verification_key = cbr::test::GetVerificationKey();

  // Act & Assert
  EXPECT_EQ(cbr::test::GetVerificationSignature(),
            verification_key.Sign(kMessage));
}

TEST_F(CatsxpAdsVerificationKeyTest, Verify) {
  // Arrange
  cbr::VerificationKey verification_key = cbr::test::GetVerificationKey();

  // Act & Assert
  EXPECT_TRUE(
      verification_key.Verify(cbr::test::GetVerificationSignature(), kMessage));
}

TEST_F(CatsxpAdsVerificationKeyTest,
       FailToVerifyWithInvalidVerificationSignature) {
  // Arrange
  cbr::VerificationKey verification_key = cbr::test::GetVerificationKey();

  // Act & Assert
  EXPECT_FALSE(verification_key.Verify(
      cbr::test::GetInvalidVerificationSignature(), kMessage));
}

}  // namespace catsxp_ads
