/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/catalog_permission_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"

namespace catsxp_ads {

bool HasCatalogPermission() {
  if (!DoesCatalogExist()) {
    BLOG(2, "Catalog does not exist");
    return false;
  }

  if (HasCatalogExpired()) {
    BLOG(2, "Catalog has expired");
    return false;
  }

  return true;
}

}  // namespace catsxp_ads
