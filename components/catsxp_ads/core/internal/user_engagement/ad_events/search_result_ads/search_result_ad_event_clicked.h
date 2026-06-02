/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_CLICKED_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_CLICKED_H_

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_interface.h"

namespace catsxp_ads {

struct SearchResultAdInfo;

class SearchResultAdEventClicked final
    : public AdEventInterface<SearchResultAdInfo> {
 public:
  // AdEventInterface:
  void FireEvent(const SearchResultAdInfo& ad,
                 ResultCallback callback) override;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_CLICKED_H_
