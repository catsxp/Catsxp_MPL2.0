/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_TEST_CONFIRMATIONS_DELEGATE_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_TEST_CONFIRMATIONS_DELEGATE_MOCK_H_

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmations_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class ConfirmationsDelegateMock : public ConfirmationDelegate {
 public:
  ConfirmationsDelegateMock();

  ConfirmationsDelegateMock(const ConfirmationsDelegateMock&) = delete;
  ConfirmationsDelegateMock& operator=(const ConfirmationsDelegateMock&) =
      delete;

  ~ConfirmationsDelegateMock() override;

  MOCK_METHOD(void, OnDidConfirm, (const ConfirmationInfo&));
  MOCK_METHOD(void, OnFailedToConfirm, (const ConfirmationInfo&));
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_TEST_CONFIRMATIONS_DELEGATE_MOCK_H_
