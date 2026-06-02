/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/new_tab_page_ads/new_tab_page_ad_event_media_play.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_events.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_info.h"

namespace catsxp_ads {

void NewTabPageAdEventMediaPlay::FireEvent(const NewTabPageAdInfo& ad,
                                           ResultCallback callback) {
  RecordAdEvent(ad, mojom::ConfirmationType::kMediaPlay, std::move(callback));
}

}  // namespace catsxp_ads
