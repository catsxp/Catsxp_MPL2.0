/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_VERIFICATION_SIGNATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_VERIFICATION_SIGNATURE_H_

#include <optional>
#include <ostream>
#include <string>

#include "base/check.h"
#include "catsxp/components/challenge_bypass_ristretto/verification_signature.h"

namespace catsxp_ads::cbr {

// A `VerificationSignature` which can be verified given the `VerificationKey`
// and message.

class VerificationSignature final {
 public:
  VerificationSignature();
  explicit VerificationSignature(
      const std::string& verification_signature_base64);
  explicit VerificationSignature(
      const challenge_bypass_ristretto::VerificationSignature&
          verification_signature);

  VerificationSignature(const VerificationSignature&);
  VerificationSignature& operator=(const VerificationSignature&);

  VerificationSignature(VerificationSignature&&) noexcept;
  VerificationSignature& operator=(VerificationSignature&&) noexcept;

  ~VerificationSignature();

  bool operator==(const VerificationSignature&) const;

  bool has_value() const {
    return verification_signature_ && verification_signature_.has_value();
  }

  challenge_bypass_ristretto::VerificationSignature& get() {
    CHECK(verification_signature_);
    return *verification_signature_;
  }

  const challenge_bypass_ristretto::VerificationSignature& get() const {
    CHECK(verification_signature_);
    return *verification_signature_;
  }

  static VerificationSignature DecodeBase64(
      const std::string& verification_signature_base64);
  std::optional<std::string> EncodeBase64() const;

 private:
  std::optional<challenge_bypass_ristretto::VerificationSignature>
      verification_signature_;
};

std::ostream& operator<<(std::ostream& os,
                         const VerificationSignature& verification_signature);

}  // namespace catsxp_ads::cbr

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_VERIFICATION_SIGNATURE_H_
