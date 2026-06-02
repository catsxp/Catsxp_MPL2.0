/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_payment_tokens/user_data/redeem_payment_tokens_user_data_builder.h"

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/platform_user_data.h"
#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/summary_user_data.h"

namespace catsxp_ads {

base::DictValue BuildRedeemPaymentTokensUserData(
    const PaymentTokenList& payment_tokens) {
  base::DictValue user_data;

  user_data.Merge(BuildPlatformUserData());
  user_data.Merge(BuildSummaryUserData(payment_tokens));

  return user_data;
}

}  // namespace catsxp_ads
