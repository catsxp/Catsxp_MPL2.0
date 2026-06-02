/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_VERIFICATION_KEY_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_VERIFICATION_KEY_H_

#include <optional>
#include <string>

#include "catsxp/components/challenge_bypass_ristretto/verification_key.h"

namespace catsxp_ads::cbr {

class VerificationSignature;

// A shared `VerificationKey` for proving and verifying the validity of an
// `UnblindedToken`. (K = H_2(t, W)).

class VerificationKey final {
 public:
  explicit VerificationKey(
      const challenge_bypass_ristretto::VerificationKey& verification_key);

  challenge_bypass_ristretto::VerificationKey& get() {
    return verification_key_;
  }

  const challenge_bypass_ristretto::VerificationKey& get() const {
    return verification_key_;
  }

  std::optional<VerificationSignature> Sign(const std::string& message);

  [[nodiscard]] bool Verify(const VerificationSignature& verification_signature,
                            const std::string& message);

 private:
  challenge_bypass_ristretto::VerificationKey verification_key_;
};

}  // namespace catsxp_ads::cbr

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_VERIFICATION_KEY_H_
