/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_URL_REQUESTS_GET_SIGNED_TOKENS_GET_SIGNED_TOKENS_URL_REQUEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_URL_REQUESTS_GET_SIGNED_TOKENS_GET_SIGNED_TOKENS_URL_REQUEST_UTIL_H_

#include <optional>
#include <string>

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"

namespace base {
class DictValue;
}  // namespace base

namespace catsxp_ads {

namespace cbr {
class PublicKey;
}  // namespace cbr

struct WalletInfo;

std::optional<std::string> ParseCaptchaId(const base::DictValue& dict);

void BuildAndAddConfirmationTokens(
    const cbr::UnblindedTokenList& unblinded_tokens,
    const cbr::PublicKey& public_key,
    const WalletInfo& wallet);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_URL_REQUESTS_GET_SIGNED_TOKENS_GET_SIGNED_TOKENS_URL_REQUEST_UTIL_H_
