/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_NOTIFICATION_AD_BUILDER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_NOTIFICATION_AD_BUILDER_H_

#include <string>

namespace catsxp_ads {

struct CreativeNotificationAdInfo;
struct NotificationAdInfo;

NotificationAdInfo BuildNotificationAd(
    const CreativeNotificationAdInfo& creative_ad);

NotificationAdInfo BuildNotificationAd(
    const CreativeNotificationAdInfo& creative_ad,
    const std::string& placement_id);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_NOTIFICATION_AD_BUILDER_H_
