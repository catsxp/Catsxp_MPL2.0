/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TOKEN_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TOKEN_H_

#include <optional>
#include <ostream>
#include <string>
#include <vector>

#include "base/check.h"
#include "catsxp/components/challenge_bypass_ristretto/token.h"

namespace catsxp_ads::cbr {

class BlindedToken;

// A `Token` consists of a randomly chosen preimage and blinding factor. Since a
// `Token` includes the blinding factor it should be treated as a client secret
// and NEVER revealed to the server.

class Token final {
 public:
  Token();
  explicit Token(const std::string& token_base64);

  Token(const Token&);
  Token& operator=(const Token&);

  Token(Token&&) noexcept;
  Token& operator=(Token&&) noexcept;

  ~Token();

  bool operator==(const Token&) const;

  bool has_value() const { return token_.has_value(); }

  challenge_bypass_ristretto::Token& get() {
    CHECK(token_);
    return *token_;
  }

  const challenge_bypass_ristretto::Token& get() const {
    CHECK(token_);
    return *token_;
  }

  static Token DecodeBase64(const std::string& token_base64);
  std::optional<std::string> EncodeBase64() const;

  std::optional<BlindedToken> Blind();

 private:
  std::optional<challenge_bypass_ristretto::Token> token_;
};

std::ostream& operator<<(std::ostream& os, const Token& token);

using TokenList = std::vector<Token>;

}  // namespace catsxp_ads::cbr

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TOKEN_H_
