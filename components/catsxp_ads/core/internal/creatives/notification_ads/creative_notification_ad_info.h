/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_CREATIVE_NOTIFICATION_AD_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_CREATIVE_NOTIFICATION_AD_INFO_H_

#include <string>
#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"

namespace catsxp_ads {

struct CreativeNotificationAdInfo final : CreativeAdInfo {
  CreativeNotificationAdInfo();
  explicit CreativeNotificationAdInfo(const CreativeAdInfo& creative_ad);

  bool operator==(const CreativeNotificationAdInfo&) const = default;

  std::string title;
  std::string body;
};

using CreativeNotificationAdList = std::vector<CreativeNotificationAdInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_CREATIVE_NOTIFICATION_AD_INFO_H_
