/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/test/permission_rules_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/test/catalog_permission_rule_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/test/confirmation_tokens_permission_rule_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/test/issuers_permission_rule_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/test/user_activity_permission_rule_test_util.h"

namespace catsxp_ads::test {

void ForcePermissionRules() {
  ForceCatalogPermissionRule();
  ForceConfirmationTokensPermissionRule();
  ForceIssuersPermissionRule();
  ForceUserActivityPermissionRule();
}

}  // namespace catsxp_ads::test
