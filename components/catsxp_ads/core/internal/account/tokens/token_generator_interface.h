/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_GENERATOR_INTERFACE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_GENERATOR_INTERFACE_H_

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token.h"

namespace catsxp_ads {

class TokenGeneratorInterface {
 public:
  virtual ~TokenGeneratorInterface() = default;

  // Generates a list of cryptographic tokens that can be redeemed for purposes
  // such as privacy-preserving ad interactions.
  virtual cbr::TokenList Generate(size_t count) const = 0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_GENERATOR_INTERFACE_H_
