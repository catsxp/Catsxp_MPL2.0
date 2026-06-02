/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/blinded_token_util.h"

#include <optional>

namespace catsxp_ads::cbr {

BlindedTokenList BlindTokens(const TokenList& tokens) {
  BlindedTokenList blinded_tokens;
  blinded_tokens.reserve(tokens.size());

  for (Token token : tokens) {
    if (!token.has_value()) {
      return {};
    }

    std::optional<BlindedToken> blinded_token = token.Blind();
    if (!blinded_token) {
      return {};
    }

    blinded_tokens.push_back(*blinded_token);
  }

  return blinded_tokens;
}

std::vector<challenge_bypass_ristretto::BlindedToken> ToRawBlindedTokens(
    const BlindedTokenList& blinded_tokens) {
  std::vector<challenge_bypass_ristretto::BlindedToken> raw_blinded_tokens;
  raw_blinded_tokens.reserve(blinded_tokens.size());

  for (const auto& blinded_token : blinded_tokens) {
    if (!blinded_token.has_value()) {
      return {};
    }

    raw_blinded_tokens.push_back(blinded_token.get());
  }

  return raw_blinded_tokens;
}

}  // namespace catsxp_ads::cbr
