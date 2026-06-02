/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ad_units/notification_ad/test/notification_ad_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ads_database_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/notification_ad_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/notification_ad_manager.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/test/creative_notification_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/notification_ad/notification_ad_info.h"

namespace catsxp_ads::test {

NotificationAdInfo BuildNotificationAd(bool use_random_uuids) {
  const CreativeNotificationAdInfo creative_ad =
      BuildCreativeNotificationAd(use_random_uuids);
  return BuildNotificationAd(creative_ad);
}

NotificationAdInfo BuildAndSaveNotificationAd(bool use_random_uuids) {
  const CreativeNotificationAdInfo creative_ad =
      BuildCreativeNotificationAd(use_random_uuids);
  database::SaveCreativeNotificationAds({creative_ad});
  const NotificationAdInfo ad = BuildNotificationAd(creative_ad);
  NotificationAdManager::GetInstance().Add(ad);
  return ad;
}

}  // namespace catsxp_ads::test
