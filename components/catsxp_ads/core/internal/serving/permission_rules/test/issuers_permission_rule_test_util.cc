/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/test/issuers_permission_rule_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/test/issuers_test_util.h"

namespace catsxp_ads::test {

void ForceIssuersPermissionRule() {
  BuildAndSetIssuers();
}

}  // namespace catsxp_ads::test
