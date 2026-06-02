/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/new_tab_page_ads/new_tab_page_ad_event_viewed.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_events.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_info.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads {

void NewTabPageAdEventViewed::FireEvent(const NewTabPageAdInfo& ad,
                                        ResultCallback callback) {
  RecordAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                std::move(callback));
}

}  // namespace catsxp_ads
