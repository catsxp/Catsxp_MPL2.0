/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_TEST_CONFIRMATION_TOKENS_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_TEST_CONFIRMATION_TOKENS_TEST_UTIL_H_

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_token_info.h"

namespace catsxp_ads {

namespace test {

// Call this function to refill confirmation tokens for testing purposes with
// random unblinded tokens.
ConfirmationTokenList RefillRandomConfirmationTokens(size_t count);

// Call this function to refill confirmation tokens for testing purposes if
// code paths call `Confirmations::Confirm`, `MaybeGetConfirmationToken`, or
// `BuildReward`. If code paths call `RefillConfirmationTokens::MaybeRefill`,
// call `MockTokenGenerator` instead and do not call this function.
ConfirmationTokenList RefillConfirmationTokens(size_t count);

ConfirmationTokenInfo BuildConfirmationToken();
ConfirmationTokenList BuildConfirmationTokens(size_t count);

}  // namespace test

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_TEST_CONFIRMATION_TOKENS_TEST_UTIL_H_
