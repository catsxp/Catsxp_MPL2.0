/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TEST_FAKE_TOKEN_GENERATOR_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TEST_FAKE_TOKEN_GENERATOR_H_

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/token_generator_interface.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token.h"

namespace catsxp_ads {

// A test double for `TokenGeneratorInterface` that returns a fixed list of
// tokens. Call `SetTokens` to configure the tokens returned by `Generate`.
class FakeTokenGenerator : public TokenGeneratorInterface {
 public:
  FakeTokenGenerator();

  FakeTokenGenerator(const FakeTokenGenerator&) = delete;
  FakeTokenGenerator& operator=(const FakeTokenGenerator&) = delete;

  ~FakeTokenGenerator() override;

  void SetTokens(cbr::TokenList tokens);

  // TokenGeneratorInterface:
  cbr::TokenList Generate(size_t count) const override;

 private:
  cbr::TokenList tokens_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TEST_FAKE_TOKEN_GENERATOR_H_
