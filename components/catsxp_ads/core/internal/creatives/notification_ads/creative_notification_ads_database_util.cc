/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ads_database_util.h"

#include "base/functional/bind.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ads_database_table.h"

namespace catsxp_ads::database {

void SaveCreativeNotificationAds(
    const CreativeNotificationAdList& creative_ads) {
  table::CreativeNotificationAds database_table;
  database_table.Save(creative_ads, base::BindOnce([](bool success) {
                        if (!success) {
                          return BLOG(
                              0, "Failed to save creative notification ads");
                        }

                        BLOG(3, "Successfully saved creative notification ads");
                      }));
}

}  // namespace catsxp_ads::database
