/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/test/fake_token_generator.h"

#include "base/check_op.h"

namespace catsxp_ads {

FakeTokenGenerator::FakeTokenGenerator() = default;

FakeTokenGenerator::~FakeTokenGenerator() = default;

void FakeTokenGenerator::SetTokens(cbr::TokenList tokens) {
  tokens_ = std::move(tokens);
}

cbr::TokenList FakeTokenGenerator::Generate(size_t count) const {
  CHECK_LE(count, tokens_.size());

  cbr::TokenList tokens(tokens_);
  tokens.resize(count);
  return tokens;
}

}  // namespace catsxp_ads
