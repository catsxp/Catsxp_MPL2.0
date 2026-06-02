/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ad_units/notification_ad/notification_ad_handler_util.h"

#include "catsxp/components/catsxp_ads/core/internal/ads_client/ads_client_util.h"
#include "catsxp/components/catsxp_ads/core/internal/application_state/browser_manager.h"
#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client.h"

namespace catsxp_ads {

bool ShouldServe() {
  return UserHasOptedInToNotificationAds();
}

bool CanServeIfUserIsActive() {
  return !IsMobile();
}

bool CanServeAtRegularIntervals() {
  return IsMobile();
}

bool ShouldServeAtRegularIntervals() {
  return ShouldServe() &&
         (BrowserManager::GetInstance().IsInForeground() ||
          GetAdsClient().CanShowNotificationAdsWhileBrowserIsBackgrounded()) &&
         GetMaximumNotificationAdsPerHour() > 0;
}

}  // namespace catsxp_ads
