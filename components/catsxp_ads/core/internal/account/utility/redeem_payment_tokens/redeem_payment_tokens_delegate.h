/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_REDEEM_PAYMENT_TOKENS_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_REDEEM_PAYMENT_TOKENS_DELEGATE_H_

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"

namespace catsxp_ads {

class RedeemPaymentTokensDelegate {
 public:
  // Invoked to tell the delegate that the `payment_tokens` were successfully
  // redeemed.
  virtual void OnDidRedeemPaymentTokens(
      const PaymentTokenList& payment_tokens) {}

  // Invoked to tell the delegate that the payment tokens failed to redeem.
  virtual void OnFailedToRedeemPaymentTokens() {}

  // Invoked to tell the delegate that payment token redemption is scheduled for
  // `redeem_at`.
  virtual void OnDidScheduleNextPaymentTokenRedemption(base::Time redeem_at) {}

  // Invoked to tell the delegate that we will retry redeeming payment tokens at
  // `retry_at`.
  virtual void OnWillRetryRedeemingPaymentTokens(base::Time retry_at) {}

  // Invoked to tell the delegate that we retried redeeming payment tokens.
  virtual void OnDidRetryRedeemingPaymentTokens() {}

 protected:
  virtual ~RedeemPaymentTokensDelegate() = default;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_REDEEM_PAYMENT_TOKENS_DELEGATE_H_
