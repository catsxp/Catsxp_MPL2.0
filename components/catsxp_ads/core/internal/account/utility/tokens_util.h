/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_TOKENS_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_TOKENS_UTIL_H_

#include <optional>

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/blinded_token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/signed_token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"

namespace base {
class DictValue;
}  // namespace base

namespace catsxp_ads {

namespace cbr {
class PublicKey;
}  // namespace cbr

std::optional<cbr::PublicKey> ParsePublicKey(const base::DictValue& dict);

std::optional<cbr::SignedTokenList> ParseSignedTokens(
    const base::DictValue& dict);

std::optional<cbr::UnblindedTokenList> ParseVerifyAndUnblindTokens(
    const base::DictValue& dict,
    const cbr::TokenList& tokens,
    const cbr::BlindedTokenList& blinded_tokens,
    const cbr::PublicKey& public_key);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_TOKENS_UTIL_H_
