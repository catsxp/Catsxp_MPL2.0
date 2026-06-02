/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_REDEEM_PAYMENT_TOKENS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_REDEEM_PAYMENT_TOKENS_H_

#include "base/check_op.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_payment_tokens/redeem_payment_tokens_delegate.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/url_response_result.h"
#include "catsxp/components/catsxp_ads/core/internal/account/wallet/wallet_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/timer/backoff_timer.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

class RedeemPaymentTokens final {
 public:
  RedeemPaymentTokens();

  RedeemPaymentTokens(const RedeemPaymentTokens&) = delete;
  RedeemPaymentTokens& operator=(const RedeemPaymentTokens&) = delete;

  ~RedeemPaymentTokens();

  void SetDelegate(RedeemPaymentTokensDelegate* delegate) {
    CHECK_EQ(delegate_, nullptr);
    delegate_ = delegate;
  }

  void MaybeRedeemAfterDelay(const WalletInfo& wallet);

 private:
  void RedeemAfterDelay();
  void Redeem();
  void RedeemCallback(const PaymentTokenList& payment_tokens,
                      const mojom::UrlResponseInfo& mojom_url_response);

  static UrlResponseResult<void> HandleRedeemPaymentTokensUrlResponse(
      const mojom::UrlResponseInfo& mojom_url_response);

  void SuccessfullyRedeemed(const PaymentTokenList& payment_tokens);
  void FailedToRedeem(bool should_retry);

  void ScheduleNextRedemption();

  void Retry();
  void RetryCallback();
  void StopRetrying();

  void NotifyDidRedeemPaymentTokens(
      const PaymentTokenList& payment_tokens) const;
  void NotifyFailedToRedeemPaymentTokens() const;
  void NotifyDidScheduleNextPaymentTokenRedemption(base::Time redeem_at) const;
  void NotifyWillRetryRedeemingPaymentTokens(base::Time retry_at) const;
  void NotifyDidRetryRedeemingPaymentTokens() const;

  raw_ptr<RedeemPaymentTokensDelegate> delegate_ = nullptr;  // Not owned.

  WalletInfo wallet_;

  bool is_redeeming_ = false;

  BackoffTimer timer_;

  base::WeakPtrFactory<RedeemPaymentTokens> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_REDEEM_PAYMENT_TOKENS_H_
