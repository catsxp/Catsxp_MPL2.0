/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/verification_key.h"

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/challenge_bypass_ristretto_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/verification_signature.h"

namespace catsxp_ads::cbr {

VerificationKey::VerificationKey(
    const challenge_bypass_ristretto::VerificationKey& verification_key)
    : verification_key_(verification_key) {}

std::optional<VerificationSignature> VerificationKey::Sign(
    const std::string& message) {
  return ValueOrLogError<challenge_bypass_ristretto::VerificationSignature,
                         VerificationSignature>(
      verification_key_.Sign(message));
}

bool VerificationKey::Verify(
    const VerificationSignature& verification_signature,
    const std::string& message) {
  if (!verification_signature.has_value()) {
    return false;
  }

  return verification_key_.Verify(verification_signature.get(), message)
      .value_or(false);
}

}  // namespace catsxp_ads::cbr
