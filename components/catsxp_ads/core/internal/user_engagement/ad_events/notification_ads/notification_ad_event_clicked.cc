/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/notification_ads/notification_ad_event_clicked.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_events.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/notification_ad/notification_ad_info.h"

namespace catsxp_ads {

void NotificationAdEventClicked::FireEvent(const NotificationAdInfo& ad,
                                           ResultCallback callback) {
  RecordAdEvent(ad, mojom::ConfirmationType::kClicked, std::move(callback));
}

}  // namespace catsxp_ads
