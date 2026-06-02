/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/do_not_disturb_permission_rule.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/application_state/browser_manager.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system.h"
#include "catsxp/components/catsxp_ads/core/internal/common/time/time_constraint_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/permission_rule_feature.h"

namespace catsxp_ads {

bool HasDoNotDisturbPermission() {
  if (OperatingSystem::GetInstance().GetType() !=
      OperatingSystemType::kAndroid) {
    return true;
  }

  if (BrowserManager::GetInstance().IsActive() &&
      BrowserManager::GetInstance().IsInForeground()) {
    return true;
  }

  base::Time::Exploded exploded;
  base::Time::Now().LocalExplode(&exploded);

  if (exploded.hour >= kDoNotDisturbToHour.Get() &&
      exploded.hour < kDoNotDisturbFromHour.Get()) {
    return true;
  }

  BLOG(2, "Should not disturb");
  return false;
}

}  // namespace catsxp_ads
