/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_REFILL_CONFIRMATION_TOKENS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_REFILL_CONFIRMATION_TOKENS_H_

#include <cstddef>
#include <optional>
#include <string>

#include "base/check_op.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/refill_confirmation_tokens/refill_confirmation_tokens_delegate.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/url_response_result.h"
#include "catsxp/components/catsxp_ads/core/internal/account/wallet/wallet_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/blinded_token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/timer/backoff_timer.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace base {
class DictValue;
}  // namespace base

namespace catsxp_ads {

class RefillConfirmationTokens final {
 public:
  RefillConfirmationTokens();

  RefillConfirmationTokens(const RefillConfirmationTokens&) = delete;
  RefillConfirmationTokens& operator=(const RefillConfirmationTokens&) = delete;

  ~RefillConfirmationTokens();

  void SetDelegate(RefillConfirmationTokensDelegate* delegate) {
    CHECK_EQ(delegate_, nullptr);
    delegate_ = delegate;
  }

  void MaybeRefill(const WalletInfo& wallet);

 private:
  void Refill();

  void GenerateTokens();

  bool ShouldRequestSignedTokens() const;
  void RequestSignedTokens();
  void RequestSignedTokensCallback(
      const mojom::UrlResponseInfo& mojom_url_response);
  UrlResponseResult<void> HandleRequestSignedTokensUrlResponse(
      const mojom::UrlResponseInfo& mojom_url_response);

  void GetSignedTokens();
  void GetSignedTokensCallback(
      const mojom::UrlResponseInfo& mojom_url_response);
  UrlResponseResult<void> HandleGetSignedTokensUrlResponse(
      const mojom::UrlResponseInfo& mojom_url_response);
  void ParseAndRequireCaptcha(const base::DictValue& dict) const;

  void SuccessfullyRefilled();
  void FailedToRefillAndRetry();
  void FailedToRefill();

  void Retry();
  void RetryCallback();
  void StopRetrying();

  void Reset();

  void NotifyWillRefillConfirmationTokens(size_t count) const;
  void NotifyCaptchaRequiredToRefillConfirmationTokens(
      const std::string& captcha_id) const;
  void NotifyDidRefillConfirmationTokens() const;
  void NotifyFailedToRefillConfirmationTokens() const;
  void NotifyWillRetryRefillingConfirmationTokens(base::Time retry_at) const;
  void NotifyDidRetryRefillingConfirmationTokens() const;

  raw_ptr<RefillConfirmationTokensDelegate> delegate_ = nullptr;  // Not owned.

  WalletInfo wallet_;

  std::optional<std::string> nonce_;

  std::optional<cbr::TokenList> tokens_;
  std::optional<cbr::BlindedTokenList> blinded_tokens_;

  bool is_refilling_ = false;

  BackoffTimer timer_;

  base::WeakPtrFactory<RefillConfirmationTokens> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_REFILL_CONFIRMATION_TOKENS_H_
