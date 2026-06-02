/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_NOTIFICATION_AD_CATALOG_CREATIVE_NOTIFICATION_AD_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_NOTIFICATION_AD_CATALOG_CREATIVE_NOTIFICATION_AD_INFO_H_

#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/catalog/campaign/creative_set/creative/catalog_creative_info.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/campaign/creative_set/creative/notification_ad/catalog_notification_ad_payload_info.h"

namespace catsxp_ads {

struct CatalogCreativeNotificationAdInfo final : CatalogCreativeInfo {
  bool operator==(const CatalogCreativeNotificationAdInfo&) const = default;

  CatalogNotificationAdPayloadInfo payload;
};

using CatalogCreativeNotificationAdList =
    std::vector<CatalogCreativeNotificationAdInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_NOTIFICATION_AD_CATALOG_CREATIVE_NOTIFICATION_AD_INFO_H_
