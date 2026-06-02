/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_HANDLER_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_HANDLER_UTIL_H_

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

struct SearchResultAdInfo;

void MaybeBuildAndSaveCreativeSetConversion(
    const mojom::CreativeSearchResultAdInfoPtr& mojom_creative_ad,
    mojom::SearchResultAdEventType mojom_ad_event_type);

bool IsAllowedToFireAdEvent(
    const mojom::CreativeSearchResultAdInfoPtr& mojom_creative_ad,
    mojom::SearchResultAdEventType mojom_ad_event_type);

bool ShouldFireAdEvent(const SearchResultAdInfo& ad,
                       const AdEventList& ad_events,
                       mojom::SearchResultAdEventType mojom_ad_event_type);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_HANDLER_UTIL_H_
