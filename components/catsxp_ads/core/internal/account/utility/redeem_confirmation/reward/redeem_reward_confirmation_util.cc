/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/reward/redeem_reward_confirmation_util.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/time/time_formatting_util.h"
#include "catsxp/components/catsxp_ads/core/internal/prefs/pref_util.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"

namespace catsxp_ads {

bool MaybeAddPaymentToken(const PaymentTokenInfo& payment_token) {
  if (PaymentTokenExists(payment_token)) {
    BLOG(1, "Payment token is a duplicate");
    return false;
  }

  AddPaymentTokens({payment_token});

  return true;
}

void LogPaymentTokenStatus() {
  const base::Time next_payment_token_redemption_at =
      GetProfileTimePref(prefs::kNextPaymentTokenRedemptionAt);

  BLOG(1, "You have " << PaymentTokenCount()
                      << " payment tokens which will be redeemed "
                      << FriendlyDateAndTime(next_payment_token_redemption_at));
}

}  // namespace catsxp_ads
