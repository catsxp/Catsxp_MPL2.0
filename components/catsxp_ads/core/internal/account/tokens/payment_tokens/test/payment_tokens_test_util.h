/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_TEST_PAYMENT_TOKENS_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_TEST_PAYMENT_TOKENS_TEST_UTIL_H_

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

class PaymentTokens;

namespace test {

PaymentTokens& GetPaymentTokens();
PaymentTokenList SetPaymentTokens(size_t count);

PaymentTokenInfo BuildPaymentToken(
    mojom::ConfirmationType mojom_confirmation_type,
    mojom::AdType mojom_ad_type);
PaymentTokenInfo BuildPaymentToken();
PaymentTokenList BuildPaymentTokens(size_t count);

}  // namespace test

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_TEST_PAYMENT_TOKENS_TEST_UTIL_H_
