/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_REFILL_CONFIRMATION_TOKENS_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_REFILL_CONFIRMATION_TOKENS_DELEGATE_H_

#include <cstddef>
#include <string>

#include "base/time/time.h"

namespace catsxp_ads {

class RefillConfirmationTokensDelegate {
 public:
  // Invoked to tell the delegate we will refill confirmation tokens.
  virtual void OnWillRefillConfirmationTokens(size_t count) {}

  // Invoked to tell the delegate we successfully refilled the confirmation
  // tokens.
  virtual void OnDidRefillConfirmationTokens() {}

  // Invoked to tell the delegate we failed to refill the confirmation tokens.
  virtual void OnFailedToRefillConfirmationTokens() {}

  // Invoked to tell the delegate that we will retry refilling the confirmation
  // tokens at `retry_at`.
  virtual void OnWillRetryRefillingConfirmationTokens(base::Time retry_at) {}

  // Invoked to tell the delegate that we retried refilling the confirmation
  // tokens.
  virtual void OnDidRetryRefillingConfirmationTokens() {}

  // Invoked to tell the delegate that the user must solve a scheduled captcha
  // with the given `captcha_id` before we can refill the confirmation tokens.
  virtual void OnCaptchaRequiredToRefillConfirmationTokens(
      const std::string& captcha_id) {}

 protected:
  virtual ~RefillConfirmationTokensDelegate() = default;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_REFILL_CONFIRMATION_TOKENS_DELEGATE_H_
