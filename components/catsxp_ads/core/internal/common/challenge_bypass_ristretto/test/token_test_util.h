/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TEST_TOKEN_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TEST_TOKEN_TEST_UTIL_H_

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token.h"

namespace catsxp_ads::cbr::test {

Token GetToken();
Token GetInvalidToken();
TokenList GetTokens();
TokenList GetInvalidTokens();

const TokenList& Tokens();

}  // namespace catsxp_ads::cbr::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TEST_TOKEN_TEST_UTIL_H_
