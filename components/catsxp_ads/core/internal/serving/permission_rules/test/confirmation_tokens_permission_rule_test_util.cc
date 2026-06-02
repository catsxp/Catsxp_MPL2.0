/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/test/confirmation_tokens_permission_rule_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/test/confirmation_tokens_test_util.h"

namespace catsxp_ads::test {

void ForceConfirmationTokensPermissionRule() {
  RefillConfirmationTokens(/*count=*/50);
}

}  // namespace catsxp_ads::test
