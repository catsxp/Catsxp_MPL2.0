/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKEN_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKEN_UTIL_H_

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"

namespace catsxp_ads {

const PaymentTokenList& GetAllPaymentTokens();

void AddPaymentTokens(const PaymentTokenList& payment_tokens);

void RemovePaymentTokens(const PaymentTokenList& payment_tokens);

bool PaymentTokenExists(const PaymentTokenInfo& payment_token);

bool PaymentTokensIsEmpty();

size_t PaymentTokenCount();

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKEN_UTIL_H_
