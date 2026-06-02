/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/verification_signature_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/challenge_bypass_ristretto_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/verification_signature.h"

namespace catsxp_ads::cbr::test {

VerificationSignature GetVerificationSignature() {
  return VerificationSignature(kVerificationSignatureBase64);
}

VerificationSignature GetInvalidVerificationSignature() {
  return VerificationSignature(kInvalidBase64);
}

}  // namespace catsxp_ads::cbr::test
