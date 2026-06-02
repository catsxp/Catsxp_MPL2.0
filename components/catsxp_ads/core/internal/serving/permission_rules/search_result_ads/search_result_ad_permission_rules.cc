/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/search_result_ads/search_result_ad_permission_rules.h"

#include <vector>

#include "base/trace_event/trace_event.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/ads_per_day_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/ads_per_hour_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_util.h"
#include "catsxp/components/catsxp_ads/core/public/ads_constants.h"

namespace catsxp_ads {

// static
bool SearchResultAdPermissionRules::HasPermission(
    const AdEventList& ad_events) {
  TRACE_EVENT(kTraceEventCategory,
              "SearchResultAdPermissionRules::HasPermission");

  if (!UserHasJoinedCatsxpRewards()) {
    // If the user has not joined Catsxp Rewards, always grant permission.
    return true;
  }

  if (!PermissionRulesBase::HasPermission()) {
    return false;
  }

  const std::vector<base::Time> history = ToHistory(ad_events);

  if (!HasAdsPerDayPermission(history,
                              /*cap=*/kMaximumSearchResultAdsPerDay.Get())) {
    return false;
  }

  if (!HasAdsPerHourPermission(history,
                               /*cap=*/kMaximumSearchResultAdsPerHour.Get())) {
    return false;
  }

  return true;
}

}  // namespace catsxp_ads
