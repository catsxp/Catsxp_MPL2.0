/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/ads_per_day_permission_rule.h"

#include "base/containers/span.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/time/time_constraint_util.h"

namespace catsxp_ads {

bool HasAdsPerDayPermission(base::span<const base::Time> history, size_t cap) {
  if (!DoesHistoryRespectRollingTimeConstraint(
          history, /*time_constraint=*/base::Days(1), cap)) {
    BLOG(2, "You have exceeded the allowed ads per day");
    return false;
  }

  return true;
}

}  // namespace catsxp_ads
