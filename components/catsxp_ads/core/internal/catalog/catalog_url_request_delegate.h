/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_URL_REQUEST_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_URL_REQUEST_DELEGATE_H_

#include "base/time/time.h"

namespace catsxp_ads {

struct CatalogInfo;

class CatalogUrlRequestDelegate {
 public:
  // Invoked to tell the delegate we will fetch the catalog at `fetch_at`.
  virtual void OnWillFetchCatalog(base::Time fetch_at) {}

  // Invoked to tell the delegate we successfully fetched the `catalog`.
  virtual void OnDidFetchCatalog(const CatalogInfo& catalog) {}

  // Invoked to tell the delegate we failed to fetch the catalog.
  virtual void OnFailedToFetchCatalog() {}

  // Invoked to tell the delegate we will retry fetching the catalog at
  // `retry_at`.
  virtual void OnWillRetryFetchingCatalog(base::Time retry_at) {}

  // Invoked to tell the delegate we retried fetching the catalog.
  virtual void OnDidRetryFetchingCatalog() {}

 protected:
  virtual ~CatalogUrlRequestDelegate() = default;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_URL_REQUEST_DELEGATE_H_
