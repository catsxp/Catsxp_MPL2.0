/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token_util.h"

namespace catsxp_ads::cbr {

std::vector<challenge_bypass_ristretto::Token> ToRawTokens(
    const TokenList& tokens) {
  std::vector<challenge_bypass_ristretto::Token> raw_tokens;
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
