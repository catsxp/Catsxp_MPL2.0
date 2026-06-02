/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TEST_ISSUERS_DELEGATE_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TEST_ISSUERS_DELEGATE_MOCK_H_

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class IssuersDelegateMock : public IssuersDelegate {
 public:
  IssuersDelegateMock();

  IssuersDelegateMock(const IssuersDelegateMock&) = delete;
  IssuersDelegateMock& operator=(const IssuersDelegateMock&) = delete;

  ~IssuersDelegateMock() override;

  MOCK_METHOD(void, OnWillFetchIssuers, (base::Time));
  MOCK_METHOD(void, OnDidFetchIssuers, (const IssuersInfo&));
  MOCK_METHOD(void, OnFailedToFetchIssuers, ());
  MOCK_METHOD(void, OnWillRetryFetchingIssuers, (base::Time));
  MOCK_METHOD(void, OnDidRetryFetchingIssuers, ());
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TEST_ISSUERS_DELEGATE_MOCK_H_
