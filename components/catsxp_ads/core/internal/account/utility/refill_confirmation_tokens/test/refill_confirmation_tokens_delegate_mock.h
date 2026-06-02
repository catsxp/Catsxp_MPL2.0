/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_TEST_REFILL_CONFIRMATION_TOKENS_DELEGATE_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_TEST_REFILL_CONFIRMATION_TOKENS_DELEGATE_MOCK_H_

#include <cstddef>
#include <string>

#include "catsxp/components/catsxp_ads/core/internal/account/utility/refill_confirmation_tokens/refill_confirmation_tokens_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class RefillConfirmationTokensDelegateMock
    : public RefillConfirmationTokensDelegate {
 public:
  RefillConfirmationTokensDelegateMock();

  RefillConfirmationTokensDelegateMock(
      const RefillConfirmationTokensDelegateMock&) = delete;
  RefillConfirmationTokensDelegateMock& operator=(
      const RefillConfirmationTokensDelegateMock&) = delete;

  ~RefillConfirmationTokensDelegateMock() override;

  MOCK_METHOD(void, OnWillRefillConfirmationTokens, (size_t));
  MOCK_METHOD(void, OnDidRefillConfirmationTokens, ());
  MOCK_METHOD(void, OnFailedToRefillConfirmationTokens, ());
  MOCK_METHOD(void, OnWillRetryRefillingConfirmationTokens, (base::Time));
  MOCK_METHOD(void, OnDidRetryRefillingConfirmationTokens, ());

  MOCK_METHOD(void,
              OnCaptchaRequiredToRefillConfirmationTokens,
              (const std::string&));
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_TEST_REFILL_CONFIRMATION_TOKENS_DELEGATE_MOCK_H_
