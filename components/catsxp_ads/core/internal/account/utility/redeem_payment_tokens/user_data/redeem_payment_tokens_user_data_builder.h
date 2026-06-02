/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_USER_DATA_REDEEM_PAYMENT_TOKENS_USER_DATA_BUILDER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_USER_DATA_REDEEM_PAYMENT_TOKENS_USER_DATA_BUILDER_H_

#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"

namespace catsxp_ads {

base::DictValue BuildRedeemPaymentTokensUserData(
    const PaymentTokenList& payment_tokens);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_USER_DATA_REDEEM_PAYMENT_TOKENS_USER_DATA_BUILDER_H_
