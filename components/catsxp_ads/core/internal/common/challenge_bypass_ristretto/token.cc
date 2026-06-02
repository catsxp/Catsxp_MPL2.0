/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token.h"

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/blinded_token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/challenge_bypass_ristretto_util.h"

namespace catsxp_ads::cbr {

namespace {

std::optional<challenge_bypass_ristretto::Token> Create(
    const std::string& token_base64) {
  if (token_base64.empty()) {
    return std::nullopt;
  }

  return ValueOrLogError(
      challenge_bypass_ristretto::Token::DecodeBase64(token_base64));
}

}  // namespace

Token::Token() : token_(challenge_bypass_ristretto::Token::Random()) {}

Token::Token(const std::string& token_base64) : token_(Create(token_base64)) {}

Token::Token(const Token& other) = default;

Token& Token::operator=(const Token& other) = default;

Token::Token(Token&& other) noexcept = default;

Token& Token::operator=(Token&& other) noexcept = default;

Token::~Token() = default;

bool Token::operator==(const Token& other) const {
  return EncodeBase64().value_or("") == other.EncodeBase64().value_or("");
}

Token Token::DecodeBase64(const std::string& token_base64) {
  return Token(token_base64);
}

std::optional<std::string> Token::EncodeBase64() const {
  if (!token_ || !has_value()) {
    return std::nullopt;
  }

  return token_->EncodeBase64();
}

std::optional<BlindedToken> Token::Blind() {
  if (!token_ || !has_value()) {
    return std::nullopt;
  }

  return ValueOrLogError<challenge_bypass_ristretto::BlindedToken,
                         BlindedToken>(token_->Blind());
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
  os << token.EncodeBase64().value_or("");
  return os;
}

}  // namespace catsxp_ads::cbr
