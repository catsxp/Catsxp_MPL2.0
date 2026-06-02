/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/minimum_wait_time_permission_rule.h"

#include "base/containers/span.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/time/time_constraint_util.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_feature.h"

namespace catsxp_ads {

bool HasMinimumWaitTimePermission(base::span<const base::Time> history,
                                  base::TimeDelta time_constraint) {
  if (!DoesHistoryRespectRollingTimeConstraint(history, time_constraint,
                                               /*cap=*/1)) {
    BLOG(2, "Ad cannot be shown as minimum wait time has not passed");
    return false;
  }

  return true;
}

}  // namespace catsxp_ads
