/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_TEST_REDEEM_PAYMENT_TOKENS_DELEGATE_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_TEST_REDEEM_PAYMENT_TOKENS_DELEGATE_MOCK_H_

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_payment_tokens/redeem_payment_tokens_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class RedeemPaymentTokensDelegateMock : public RedeemPaymentTokensDelegate {
 public:
  RedeemPaymentTokensDelegateMock();

  RedeemPaymentTokensDelegateMock(const RedeemPaymentTokensDelegateMock&) =
      delete;
  RedeemPaymentTokensDelegateMock& operator=(
      const RedeemPaymentTokensDelegateMock&) = delete;

  ~RedeemPaymentTokensDelegateMock() override;

  MOCK_METHOD(void, OnDidRedeemPaymentTokens, (const PaymentTokenList&));
  MOCK_METHOD(void, OnFailedToRedeemPaymentTokens, ());
  MOCK_METHOD(void, OnDidScheduleNextPaymentTokenRedemption, (base::Time));
  MOCK_METHOD(void, OnWillRetryRedeemingPaymentTokens, (base::Time));
  MOCK_METHOD(void, OnDidRetryRedeemingPaymentTokens, ());
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_TEST_REDEEM_PAYMENT_TOKENS_DELEGATE_MOCK_H_
