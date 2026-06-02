/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/notification_ad_builder.h"

#include "base/uuid.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ad_info.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/notification_ad/notification_ad_info.h"

namespace catsxp_ads {

NotificationAdInfo BuildNotificationAd(
    const CreativeNotificationAdInfo& creative_ad) {
  const std::string placement_id =
      base::Uuid::GenerateRandomV4().AsLowercaseString();
  return BuildNotificationAd(creative_ad, placement_id);
}

NotificationAdInfo BuildNotificationAd(
    const CreativeNotificationAdInfo& creative_ad,
    const std::string& placement_id) {
  NotificationAdInfo ad;

  ad.type = mojom::AdType::kNotificationAd;
  ad.placement_id = placement_id;
  ad.creative_instance_id = creative_ad.creative_instance_id;
  ad.creative_set_id = creative_ad.creative_set_id;
  ad.campaign_id = creative_ad.campaign_id;
  ad.advertiser_id = creative_ad.advertiser_id;
  ad.segment = creative_ad.segment;
  ad.title = creative_ad.title;
  ad.body = creative_ad.body;
  ad.target_url = creative_ad.target_url;

  return ad;
}

}  // namespace catsxp_ads
