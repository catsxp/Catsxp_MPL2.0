/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_SIGNED_TOKEN_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_SIGNED_TOKEN_H_

#include <optional>
#include <ostream>
#include <string>
#include <vector>

#include "base/check.h"
#include "catsxp/components/challenge_bypass_ristretto/signed_token.h"

namespace catsxp_ads::cbr {

// A `SignedToken` is the result of signing a `BlindedToken`.

class SignedToken final {
 public:
  SignedToken();
  explicit SignedToken(const std::string& signed_token_base64);
  explicit SignedToken(
      const challenge_bypass_ristretto::SignedToken& signed_token);

  SignedToken(const SignedToken&);
  SignedToken& operator=(const SignedToken&);

  SignedToken(SignedToken&&) noexcept;
  SignedToken& operator=(SignedToken&&) noexcept;

  ~SignedToken();

  bool operator==(const SignedToken&) const;

  bool has_value() const { return signed_token_.has_value(); }

  challenge_bypass_ristretto::SignedToken& get() {
    CHECK(signed_token_);
    return *signed_token_;
  }

  const challenge_bypass_ristretto::SignedToken& get() const {
    CHECK(signed_token_);
    return *signed_token_;
  }

  static SignedToken DecodeBase64(const std::string& signed_token_base64);
  std::optional<std::string> EncodeBase64() const;

 private:
  std::optional<challenge_bypass_ristretto::SignedToken> signed_token_;
};

std::ostream& operator<<(std::ostream& os, const SignedToken& signed_token);

using SignedTokenList = std::vector<SignedToken>;

}  // namespace catsxp_ads::cbr

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_SIGNED_TOKEN_H_
