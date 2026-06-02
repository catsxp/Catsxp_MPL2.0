/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/signed_token_util.h"

namespace catsxp_ads::cbr {

std::vector<challenge_bypass_ristretto::SignedToken> ToRawSignedTokens(
    const SignedTokenList& tokens) {
  std::vector<challenge_bypass_ristretto::SignedToken> raw_tokens;
  raw_tokens.reserve(tokens.size());

  for (const auto& token : tokens) {
    if (!token.has_value()) {
      return {};
    }

    raw_tokens.push_back(token.get());
  }

  return raw_tokens;
}

}  // namespace catsxp_ads::cbr
