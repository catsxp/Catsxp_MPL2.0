/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_GENERATOR_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_GENERATOR_H_

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/token_generator_interface.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token.h"

namespace catsxp_ads {

class TokenGenerator final : public TokenGeneratorInterface {
 public:
  // TokenGeneratorInterface:
  cbr::TokenList Generate(size_t count) const override;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_GENERATOR_H_
