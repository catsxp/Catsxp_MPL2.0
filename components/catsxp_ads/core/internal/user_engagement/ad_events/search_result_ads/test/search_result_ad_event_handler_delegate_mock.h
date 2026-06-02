/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_TEST_SEARCH_RESULT_AD_EVENT_HANDLER_DELEGATE_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_TEST_SEARCH_RESULT_AD_EVENT_HANDLER_DELEGATE_MOCK_H_

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/search_result_ads/search_result_ad_event_handler_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class SearchResultAdEventHandlerDelegateMock
    : public SearchResultAdEventHandlerDelegate {
 public:
  SearchResultAdEventHandlerDelegateMock();

  SearchResultAdEventHandlerDelegateMock(
      const SearchResultAdEventHandlerDelegateMock&) = delete;
  SearchResultAdEventHandlerDelegateMock& operator=(
      const SearchResultAdEventHandlerDelegateMock&) = delete;

  ~SearchResultAdEventHandlerDelegateMock() override;

  MOCK_METHOD(void,
              OnDidFireSearchResultAdServedEvent,
              (const SearchResultAdInfo&));
  MOCK_METHOD(void,
              OnDidFireSearchResultAdViewedEvent,
              (const SearchResultAdInfo&));
  MOCK_METHOD(void,
              OnWillFireSearchResultAdClickedEvent,
              (const SearchResultAdInfo&));
  MOCK_METHOD(void,
              OnDidFireSearchResultAdClickedEvent,
              (const SearchResultAdInfo&));
  MOCK_METHOD(void,
              OnFailedToFireSearchResultAdEvent,
              (const SearchResultAdInfo&, mojom::SearchResultAdEventType));
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_TEST_SEARCH_RESULT_AD_EVENT_HANDLER_DELEGATE_MOCK_H_
