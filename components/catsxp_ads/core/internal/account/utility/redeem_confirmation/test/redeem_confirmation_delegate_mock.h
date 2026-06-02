/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_TEST_REDEEM_CONFIRMATION_DELEGATE_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_TEST_REDEEM_CONFIRMATION_DELEGATE_MOCK_H_

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/redeem_confirmation_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class RedeemConfirmationDelegateMock : public RedeemConfirmationDelegate {
 public:
  RedeemConfirmationDelegateMock();

  RedeemConfirmationDelegateMock(const RedeemConfirmationDelegateMock&) =
      delete;
  RedeemConfirmationDelegateMock& operator=(
      const RedeemConfirmationDelegateMock&) = delete;

  ~RedeemConfirmationDelegateMock() override;

  MOCK_METHOD(void, OnDidRedeemConfirmation, (const ConfirmationInfo&));
  MOCK_METHOD(void,
              OnFailedToRedeemConfirmation,
              (const ConfirmationInfo&, bool));
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_TEST_REDEEM_CONFIRMATION_DELEGATE_MOCK_H_
