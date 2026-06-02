/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_TEST_CATALOG_URL_REQUEST_DELEGATE_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_TEST_CATALOG_URL_REQUEST_DELEGATE_MOCK_H_

#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_url_request_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class CatalogUrlRequestDelegateMock : public CatalogUrlRequestDelegate {
 public:
  CatalogUrlRequestDelegateMock();

  CatalogUrlRequestDelegateMock(const CatalogUrlRequestDelegateMock&) = delete;
  CatalogUrlRequestDelegateMock& operator=(
      const CatalogUrlRequestDelegateMock&) = delete;

  ~CatalogUrlRequestDelegateMock() override;

  MOCK_METHOD(void, OnWillFetchCatalog, (base::Time));
  MOCK_METHOD(void, OnDidFetchCatalog, (const CatalogInfo&));
  MOCK_METHOD(void, OnFailedToFetchCatalog, ());
  MOCK_METHOD(void, OnWillRetryFetchingCatalog, (base::Time));
  MOCK_METHOD(void, OnDidRetryFetchingCatalog, ());
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_TEST_CATALOG_URL_REQUEST_DELEGATE_MOCK_H_
