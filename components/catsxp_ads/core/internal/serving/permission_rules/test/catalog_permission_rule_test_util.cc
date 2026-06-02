/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/test/catalog_permission_rule_test_util.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_util.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/test/catalog_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"

namespace catsxp_ads::test {

void ForceCatalogPermissionRule() {
  SetCatalogId(kCatalogId);
  SetCatalogVersion(1);
  SetCatalogPing(base::Hours(2));
  SetCatalogLastUpdated(Now());
}

}  // namespace catsxp_ads::test
