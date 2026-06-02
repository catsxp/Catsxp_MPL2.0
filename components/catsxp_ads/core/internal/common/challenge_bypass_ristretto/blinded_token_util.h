/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_BLINDED_TOKEN_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_BLINDED_TOKEN_UTIL_H_

#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/blinded_token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token.h"
#include "catsxp/components/challenge_bypass_ristretto/blinded_token.h"

namespace catsxp_ads::cbr {

BlindedTokenList BlindTokens(const TokenList& tokens);

std::vector<challenge_bypass_ristretto::BlindedToken> ToRawBlindedTokens(
    const BlindedTokenList& blinded_tokens);

}  // namespace catsxp_ads::cbr

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_BLINDED_TOKEN_UTIL_H_
