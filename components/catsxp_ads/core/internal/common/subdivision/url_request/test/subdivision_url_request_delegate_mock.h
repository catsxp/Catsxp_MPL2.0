/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_TEST_SUBDIVISION_URL_REQUEST_DELEGATE_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_TEST_SUBDIVISION_URL_REQUEST_DELEGATE_MOCK_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/url_request/subdivision_url_request_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class SubdivisionUrlRequestDelegateMock : public SubdivisionUrlRequestDelegate {
 public:
  SubdivisionUrlRequestDelegateMock();

  SubdivisionUrlRequestDelegateMock(const SubdivisionUrlRequestDelegateMock&) =
      delete;
  SubdivisionUrlRequestDelegateMock& operator=(
      const SubdivisionUrlRequestDelegateMock&) = delete;

  ~SubdivisionUrlRequestDelegateMock() override;

  MOCK_METHOD(void, OnWillFetchSubdivision, (base::Time));
  MOCK_METHOD(void, OnDidFetchSubdivision, (const std::string&));
  MOCK_METHOD(void, OnFailedToFetchSubdivision, ());
  MOCK_METHOD(void, OnWillRetryFetchingSubdivision, (base::Time));
  MOCK_METHOD(void, OnDidRetryFetchingSubdivision, ());
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_TEST_SUBDIVISION_URL_REQUEST_DELEGATE_MOCK_H_
