/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/browser_is_active_permission_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/application_state/browser_manager.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/permission_rule_feature.h"

namespace catsxp_ads {

bool HasBrowserIsActivePermission() {
  if (!kShouldOnlyServeAdsIfBrowserIsActive.Get()) {
    return true;
  }

  if (BrowserManager::GetInstance().IsActive() &&
      BrowserManager::GetInstance().IsInForeground()) {
    return true;
  }

  BLOG(2, "Browser window is not active");
  return false;
}

}  // namespace catsxp_ads
