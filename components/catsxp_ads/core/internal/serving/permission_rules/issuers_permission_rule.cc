/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/issuers_permission_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"

namespace catsxp_ads {

bool HasIssuersPermission() {
  if (!UserHasJoinedCatsxpRewardsAndConnectedWallet()) {
    // Allow ads if the user has not joined Catsxp Rewards and connected a
    // wallet, as issuers are not fetched in this case.
    return true;
  }

  if (HasIssuers()) {
    return true;
  }

  BLOG(2, "Missing issuers");
  return false;
}

}  // namespace catsxp_ads
