/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/notification_ads/notification_ad_event_timed_out.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/public/ad_units/notification_ad/notification_ad_info.h"

namespace catsxp_ads {

void NotificationAdEventTimedOut::FireEvent(const NotificationAdInfo& /*ad*/,
                                            ResultCallback callback) {
  std::move(callback).Run(/*success=*/true);
}

}  // namespace catsxp_ads
