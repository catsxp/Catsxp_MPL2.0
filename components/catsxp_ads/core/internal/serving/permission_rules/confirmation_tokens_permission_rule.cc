/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/confirmation_tokens_permission_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_tokens_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"

namespace catsxp_ads {

namespace {
constexpr size_t kMinimumConfirmationTokenThreshold = 10;
}  // namespace

bool HasConfirmationTokensPermission() {
  if (!UserHasJoinedCatsxpRewardsAndConnectedWallet()) {
    // Allow ads if the user has not joined Catsxp Rewards and connected a
    // wallet, as confirmation tokens are not refilled in this case.
    return true;
  }

  if (ConfirmationTokenCount() >= kMinimumConfirmationTokenThreshold) {
    return true;
  }

  BLOG(2, "You do not have enough confirmation tokens");
  return false;
}

}  // namespace catsxp_ads
