/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/search_result_ads/search_result_ad_event_clicked.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_events.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

void SearchResultAdEventClicked::FireEvent(const SearchResultAdInfo& ad,
                                           ResultCallback callback) {
  RecordAdEvent(ad, mojom::ConfirmationType::kClicked, std::move(callback));
}

}  // namespace catsxp_ads
