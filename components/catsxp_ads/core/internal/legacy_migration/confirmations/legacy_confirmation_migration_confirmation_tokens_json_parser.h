/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CONFIRMATIONS_LEGACY_CONFIRMATION_MIGRATION_CONFIRMATION_TOKENS_JSON_PARSER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CONFIRMATIONS_LEGACY_CONFIRMATION_MIGRATION_CONFIRMATION_TOKENS_JSON_PARSER_H_

#include <optional>
#include <string_view>

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_token_info.h"

namespace catsxp_ads {

struct WalletInfo;

namespace json::reader {

// Parses confirmation tokens from the legacy `confirmations.json` format.
// Tokens whose Ed25519 signature cannot be verified against the wallet public
// key are silently dropped. Returns `std::nullopt` if `json` is malformed or
// the `unblinded_tokens` key is absent.
std::optional<ConfirmationTokenList> ParseConfirmationTokens(
    std::string_view json,
    const WalletInfo& wallet);

}  // namespace json::reader

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CONFIRMATIONS_LEGACY_CONFIRMATION_MIGRATION_CONFIRMATION_TOKENS_JSON_PARSER_H_
