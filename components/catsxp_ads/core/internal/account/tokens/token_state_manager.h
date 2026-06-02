/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_STATE_MANAGER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_STATE_MANAGER_H_

#include "base/check.h"
#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_token_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_tokens.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_tokens.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads {

// Loads confirmation tokens and payment tokens from the database into memory at
// startup and provides in-memory access to both token caches.
class TokenStateManager final {
 public:
  TokenStateManager();

  TokenStateManager(const TokenStateManager&) = delete;
  TokenStateManager& operator=(const TokenStateManager&) = delete;

  ~TokenStateManager();

  static TokenStateManager& GetInstance();

  void LoadState(ResultCallback callback);

  bool IsInitialized() const { return is_initialized_; }

  const ConfirmationTokens& GetConfirmationTokens() const {
    CHECK(is_initialized_);
    return confirmation_tokens_;
  }

  ConfirmationTokens& GetConfirmationTokens() {
    CHECK(is_initialized_);
    return confirmation_tokens_;
  }

  const PaymentTokens& GetPaymentTokens() const {
    CHECK(is_initialized_);
    return payment_tokens_;
  }

  PaymentTokens& GetPaymentTokens() {
    CHECK(is_initialized_);
    return payment_tokens_;
  }

 private:
  void GetAllConfirmationTokensCallback(
      ResultCallback callback,
      bool success,
      const ConfirmationTokenList& confirmation_tokens);

  void GetAllPaymentTokensCallback(ResultCallback callback,
                                   bool success,
                                   const PaymentTokenList& payment_tokens);

  bool is_initialized_ = false;

  ConfirmationTokens confirmation_tokens_;
  PaymentTokens payment_tokens_;

  base::WeakPtrFactory<TokenStateManager> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_STATE_MANAGER_H_
