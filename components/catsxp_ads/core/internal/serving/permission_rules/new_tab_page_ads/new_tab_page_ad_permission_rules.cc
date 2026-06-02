/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/new_tab_page_ads/new_tab_page_ad_permission_rules.h"

#include <vector>

#include "base/trace_event/trace_event.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/ads_per_day_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/ads_per_hour_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/minimum_wait_time_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/user_activity_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_util.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_feature.h"
#include "catsxp/components/catsxp_ads/core/public/ads_constants.h"

namespace catsxp_ads {

// static
bool NewTabPageAdPermissionRules::HasPermission(const AdEventList& ad_events) {
  TRACE_EVENT(kTraceEventCategory,
              "NewTabPageAdPermissionRules::HasPermission");

  if (!UserHasJoinedCatsxpRewardsAndConnectedWallet()) {
    // If the user has not joined Catsxp Rewards, always grant permission.
    return true;
  }

  if (!PermissionRulesBase::HasPermission()) {
    return false;
  }

  if (!HasUserActivityPermission()) {
    return false;
  }

  const std::vector<base::Time> history = ToHistory(ad_events);

  if (!HasAdsPerDayPermission(history,
                              /*cap=*/kMaximumNewTabPageAdsPerDay.Get())) {
    return false;
  }

  if (!HasAdsPerHourPermission(history,
                               /*cap=*/kMaximumNewTabPageAdsPerHour.Get())) {
    return false;
  }

  if (!HasMinimumWaitTimePermission(
          history,
          /*time_constraint=*/kNewTabPageAdMinimumWaitTime.Get())) {
    return false;
  }

  return true;
}

}  // namespace catsxp_ads
