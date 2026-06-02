/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TEST_TOKEN_GENERATOR_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TEST_TOKEN_GENERATOR_TEST_UTIL_H_

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token.h"

namespace catsxp_ads::test {

// Call this function to mock the token generator for testing purposes if code
// paths call `RefillConfirmationTokens::MaybeRefill`, `Confirmations::Confirm`,
// `BuildRewardConfirmation`, or `BuildReward`.
void MockTokenGenerator(size_t count);

cbr::TokenList BuildTokens(size_t count);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TEST_TOKEN_GENERATOR_TEST_UTIL_H_
