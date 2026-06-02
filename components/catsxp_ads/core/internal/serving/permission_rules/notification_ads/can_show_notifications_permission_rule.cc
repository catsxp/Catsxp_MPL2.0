/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/notification_ads/can_show_notifications_permission_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/ads_client/ads_client_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client.h"

namespace catsxp_ads {

bool HasCanShowNotificationsPermission() {
  if (GetAdsClient().CanShowNotificationAds()) {
    return true;
  }

  BLOG(2, "Notifications cannot be shown");
  return false;
}

}  // namespace catsxp_ads
