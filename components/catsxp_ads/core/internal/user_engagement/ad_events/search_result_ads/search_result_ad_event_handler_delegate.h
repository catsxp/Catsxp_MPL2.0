/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_HANDLER_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_HANDLER_DELEGATE_H_

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

struct SearchResultAdInfo;

class SearchResultAdEventHandlerDelegate {
 public:
  // Invoked when the search result `ad` is served.
  virtual void OnDidFireSearchResultAdServedEvent(
      const SearchResultAdInfo& ad) {}

  // Invoked when the search result `ad` is viewed.
  virtual void OnDidFireSearchResultAdViewedEvent(
      const SearchResultAdInfo& ad) {}

  // Invoked before the click ad event for `ad` is recorded.
  virtual void OnWillFireSearchResultAdClickedEvent(
      const SearchResultAdInfo& ad) {}

  // Invoked when the search result `ad` is clicked.
  virtual void OnDidFireSearchResultAdClickedEvent(
      const SearchResultAdInfo& ad) {}

  // Invoked when the search result `ad` event fails for `mojom_ad_event_type`.
  virtual void OnFailedToFireSearchResultAdEvent(
      const SearchResultAdInfo& ad,
      mojom::SearchResultAdEventType mojom_ad_event_type) {}

 protected:
  virtual ~SearchResultAdEventHandlerDelegate() = default;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_HANDLER_DELEGATE_H_
