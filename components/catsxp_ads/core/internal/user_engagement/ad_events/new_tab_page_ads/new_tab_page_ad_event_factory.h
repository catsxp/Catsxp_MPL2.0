/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NEW_TAB_PAGE_ADS_NEW_TAB_PAGE_AD_EVENT_FACTORY_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NEW_TAB_PAGE_ADS_NEW_TAB_PAGE_AD_EVENT_FACTORY_H_

#include <memory>

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_interface.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

struct NewTabPageAdInfo;

class NewTabPageAdEventFactory final {
 public:
  // This class contains only static methods.
  NewTabPageAdEventFactory() = delete;
  NewTabPageAdEventFactory(const NewTabPageAdEventFactory&) = delete;
  NewTabPageAdEventFactory& operator=(const NewTabPageAdEventFactory&) = delete;

  static std::unique_ptr<AdEventInterface<NewTabPageAdInfo>> Build(
      mojom::NewTabPageAdEventType mojom_ad_event_type);
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NEW_TAB_PAGE_ADS_NEW_TAB_PAGE_AD_EVENT_FACTORY_H_
