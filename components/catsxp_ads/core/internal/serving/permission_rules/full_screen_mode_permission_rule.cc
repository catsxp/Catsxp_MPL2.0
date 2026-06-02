/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/full_screen_mode_permission_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/ads_client/ads_client_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/permission_rule_feature.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client.h"

namespace catsxp_ads {

bool HasFullScreenModePermission() {
  if (!kShouldOnlyServeAdsInWindowedMode.Get()) {
    return true;
  }

  if (IsMobile()) {
    return true;
  }

  if (!GetAdsClient().IsBrowserInFullScreenMode()) {
    return true;
  }

  BLOG(2, "Full screen mode");
  return false;
}

}  // namespace catsxp_ads
