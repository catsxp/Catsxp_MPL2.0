/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKENS_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKENS_UTIL_H_

#include <cstddef>
#include <optional>

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_token_info.h"

namespace catsxp_ads {

class ConfirmationTokens;

ConfirmationTokens& GetConfirmationTokens();

std::optional<ConfirmationTokenInfo> MaybeGetConfirmationToken();

void AddConfirmationTokens(const ConfirmationTokenList& confirmation_tokens);

bool RemoveConfirmationToken(const ConfirmationTokenInfo& confirmation_token);

size_t ConfirmationTokenCount();

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKENS_UTIL_H_
