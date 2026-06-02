/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/test/user_activity_permission_rule_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_manager.h"

namespace catsxp_ads::test {

void ForceUserActivityPermissionRule() {
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClosedTab);
}

}  // namespace catsxp_ads::test
