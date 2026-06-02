/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/search_result_ads/search_result_ad_event_factory.h"

#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/search_result_ads/search_result_ad_event_clicked.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/search_result_ads/search_result_ad_event_served.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/search_result_ads/search_result_ad_event_viewed.h"

namespace catsxp_ads {

std::unique_ptr<AdEventInterface<SearchResultAdInfo>>
SearchResultAdEventFactory::Build(
    mojom::SearchResultAdEventType mojom_ad_event_type) {
  switch (mojom_ad_event_type) {
    case mojom::SearchResultAdEventType::kServedImpression: {
      return std::make_unique<SearchResultAdEventServed>();
    }

    case mojom::SearchResultAdEventType::kViewedImpression: {
      return std::make_unique<SearchResultAdEventViewed>();
    }

    case mojom::SearchResultAdEventType::kClicked: {
      return std::make_unique<SearchResultAdEventClicked>();
    }
  }
}

}  // namespace catsxp_ads
