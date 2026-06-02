/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/notification_ads/notification_ad_permission_rules.h"

#include <vector>

#include "base/time/time.h"
#include "base/trace_event/trace_event.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/ads_per_day_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/ads_per_hour_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/browser_is_active_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/catalog_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/do_not_disturb_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/full_screen_mode_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/media_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/minimum_wait_time_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/network_connection_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/notification_ads/can_show_notifications_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/user_activity_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_util.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/notification_ad/notification_ad_feature.h"
#include "catsxp/components/catsxp_ads/core/public/ads_constants.h"

namespace catsxp_ads {

// static
bool NotificationAdPermissionRules::HasPermission(
    const AdEventList& ad_events) {
  TRACE_EVENT(kTraceEventCategory,
              "NotificationAdPermissionRules::HasPermission");

  if (!PermissionRulesBase::HasPermission()) {
    return false;
  }

  if (!HasUserActivityPermission()) {
    return false;
  }

  if (!HasCatalogPermission()) {
    return false;
  }

  if (!HasCanShowNotificationsPermission()) {
    return false;
  }

  if (!HasNetworkConnectionPermission()) {
    return false;
  }

  if (!HasFullScreenModePermission()) {
    return false;
  }

  if (!HasBrowserIsActivePermission()) {
    return false;
  }

  if (!HasDoNotDisturbPermission()) {
    return false;
  }

  if (!HasMediaPermission()) {
    return false;
  }

  const std::vector<base::Time> history = ToHistory(ad_events);

  if (!HasAdsPerDayPermission(history,
                              /*cap=*/kMaximumNotificationAdsPerDay.Get())) {
    return false;
  }

  if (!HasAdsPerHourPermission(history,
                               /*cap=*/GetMaximumNotificationAdsPerHour())) {
    return false;
  }

  return HasMinimumWaitTimePermission(
      history,
      /*time_constraint=*/base::Hours(1) / GetMaximumNotificationAdsPerHour());
}

}  // namespace catsxp_ads
