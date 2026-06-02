/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_TEST_CATALOG_OBSERVER_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_TEST_CATALOG_OBSERVER_MOCK_H_

#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_observer.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class CatalogObserverMock : public CatalogObserver {
 public:
  CatalogObserverMock();

  CatalogObserverMock(const CatalogObserverMock&) = delete;
  CatalogObserverMock& operator=(const CatalogObserverMock&) = delete;

  ~CatalogObserverMock() override;

  MOCK_METHOD(void, OnDidFetchCatalog, (const CatalogInfo&));
  MOCK_METHOD(void, OnFailedToFetchCatalog, ());
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_TEST_CATALOG_OBSERVER_MOCK_H_
