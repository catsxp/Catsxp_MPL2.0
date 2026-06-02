/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_OBSERVER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_OBSERVER_H_

#include "base/observer_list_types.h"

namespace catsxp_ads {

struct CatalogInfo;

class CatalogObserver : public base::CheckedObserver {
 public:
  // Invoked when the catalog is successfully fetched.
  virtual void OnDidFetchCatalog(const CatalogInfo& catalog) {}

  // Invoked when the catalog fetch fails.
  virtual void OnFailedToFetchCatalog() {}
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_OBSERVER_H_
