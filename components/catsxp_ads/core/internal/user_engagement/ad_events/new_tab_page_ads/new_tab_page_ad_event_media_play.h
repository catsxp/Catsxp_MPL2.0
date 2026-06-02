/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NEW_TAB_PAGE_ADS_NEW_TAB_PAGE_AD_EVENT_MEDIA_PLAY_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NEW_TAB_PAGE_ADS_NEW_TAB_PAGE_AD_EVENT_MEDIA_PLAY_H_

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_interface.h"

namespace catsxp_ads {

struct NewTabPageAdInfo;

class NewTabPageAdEventMediaPlay final
    : public AdEventInterface<NewTabPageAdInfo> {
 public:
  // AdEventInterface:
  void FireEvent(const NewTabPageAdInfo& ad, ResultCallback callback) override;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NEW_TAB_PAGE_ADS_NEW_TAB_PAGE_AD_EVENT_MEDIA_PLAY_H_
