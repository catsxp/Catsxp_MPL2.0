/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_NOTIFICATION_AD_CATALOG_NOTIFICATION_AD_PAYLOAD_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_NOTIFICATION_AD_CATALOG_NOTIFICATION_AD_PAYLOAD_INFO_H_

#include <string>

#include "url/gurl.h"

namespace catsxp_ads {

struct CatalogNotificationAdPayloadInfo final {
  bool operator==(const CatalogNotificationAdPayloadInfo&) const = default;

  std::string body;
  std::string title;
  GURL target_url;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_NOTIFICATION_AD_CATALOG_NOTIFICATION_AD_PAYLOAD_INFO_H_
