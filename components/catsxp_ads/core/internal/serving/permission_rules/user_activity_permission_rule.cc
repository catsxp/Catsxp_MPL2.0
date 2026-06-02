/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/user_activity_permission_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_scoring_util.h"

namespace catsxp_ads {

bool HasUserActivityPermission() {
  if (!UserHasJoinedCatsxpRewardsAndConnectedWallet()) {
    // Allow ads if the user has not joined Catsxp Rewards and connected a
    // wallet.
    return true;
  }

  if (OperatingSystem::GetInstance().GetType() == OperatingSystemType::kIOS) {
    return true;
  }

  if (WasUserActive()) {
    return true;
  }

  BLOG(2, "User was inactive");
  return false;
}

}  // namespace catsxp_ads
