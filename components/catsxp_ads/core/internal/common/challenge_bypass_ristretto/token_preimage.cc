/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token_preimage.h"

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/challenge_bypass_ristretto_util.h"

namespace catsxp_ads::cbr {

namespace {

std::optional<challenge_bypass_ristretto::TokenPreimage> Create(
    const std::string& token_preimage_base64) {
  if (token_preimage_base64.empty()) {
    return std::nullopt;
  }

  return ValueOrLogError(
      challenge_bypass_ristretto::TokenPreimage::DecodeBase64(
          token_preimage_base64));
}

}  // namespace

TokenPreimage::TokenPreimage() = default;

TokenPreimage::TokenPreimage(const std::string& token_preimage_base64)
    : token_preimage_(Create(token_preimage_base64)) {}

TokenPreimage::TokenPreimage(
    const challenge_bypass_ristretto::TokenPreimage& token_preimage)
    : token_preimage_(token_preimage) {}

TokenPreimage::TokenPreimage(const TokenPreimage& other) = default;

TokenPreimage& TokenPreimage::operator=(const TokenPreimage& other) = default;

TokenPreimage::TokenPreimage(TokenPreimage&& other) noexcept = default;

TokenPreimage& TokenPreimage::operator=(TokenPreimage&& other) noexcept =
    default;

TokenPreimage::~TokenPreimage() = default;

bool TokenPreimage::operator==(const TokenPreimage& other) const {
  return EncodeBase64().value_or("") == other.EncodeBase64().value_or("");
}

TokenPreimage TokenPreimage::DecodeBase64(
    const std::string& token_preimage_base64) {
  return TokenPreimage(token_preimage_base64);
}

std::optional<std::string> TokenPreimage::EncodeBase64() const {
  if (!token_preimage_ || !has_value()) {
    return std::nullopt;
  }

  return token_preimage_->EncodeBase64();
}

std::ostream& operator<<(std::ostream& os,
                         const TokenPreimage& token_preimage) {
  os << token_preimage.EncodeBase64().value_or("");
  return os;
}

}  // namespace catsxp_ads::cbr
