/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NEW_TAB_PAGE_ADS_TEST_NEW_TAB_PAGE_AD_EVENT_HANDLER_DELEGATE_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NEW_TAB_PAGE_ADS_TEST_NEW_TAB_PAGE_AD_EVENT_HANDLER_DELEGATE_MOCK_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/new_tab_page_ads/new_tab_page_ad_event_handler_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class NewTabPageAdEventHandlerDelegateMock
    : public NewTabPageAdEventHandlerDelegate {
 public:
  NewTabPageAdEventHandlerDelegateMock();

  NewTabPageAdEventHandlerDelegateMock(
      const NewTabPageAdEventHandlerDelegateMock&) = delete;
  NewTabPageAdEventHandlerDelegateMock& operator=(
      const NewTabPageAdEventHandlerDelegateMock&) = delete;

  ~NewTabPageAdEventHandlerDelegateMock() override;

  MOCK_METHOD(void,
              OnDidFireNewTabPageAdServedEvent,
              (const NewTabPageAdInfo&));
  MOCK_METHOD(void,
              OnDidFireNewTabPageAdViewedEvent,
              (const NewTabPageAdInfo&));
  MOCK_METHOD(void,
              OnWillFireNewTabPageAdClickedEvent,
              (const NewTabPageAdInfo&));
  MOCK_METHOD(void,
              OnDidFireNewTabPageAdClickedEvent,
              (const NewTabPageAdInfo&));
  MOCK_METHOD(void,
              OnDidFireNewTabPageAdInteractionEvent,
              (const NewTabPageAdInfo&));
  MOCK_METHOD(void,
              OnDidFireNewTabPageAdMediaPlayEvent,
              (const NewTabPageAdInfo&));
  MOCK_METHOD(void,
              OnDidFireNewTabPageAdMedia25Event,
              (const NewTabPageAdInfo&));
  MOCK_METHOD(void,
              OnDidFireNewTabPageAdMedia100Event,
              (const NewTabPageAdInfo&));
  MOCK_METHOD(void,
              OnFailedToFireNewTabPageAdEvent,
              (const std::string&,
               const std::string&,
               mojom::NewTabPageAdEventType));
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NEW_TAB_PAGE_ADS_TEST_NEW_TAB_PAGE_AD_EVENT_HANDLER_DELEGATE_MOCK_H_
