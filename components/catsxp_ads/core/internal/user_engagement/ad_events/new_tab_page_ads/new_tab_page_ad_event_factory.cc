/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/new_tab_page_ads/new_tab_page_ad_event_factory.h"

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/new_tab_page_ads/new_tab_page_ad_event_clicked.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/new_tab_page_ads/new_tab_page_ad_event_interaction.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/new_tab_page_ads/new_tab_page_ad_event_media_100.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/new_tab_page_ads/new_tab_page_ad_event_media_25.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/new_tab_page_ads/new_tab_page_ad_event_media_play.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/new_tab_page_ads/new_tab_page_ad_event_served.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/new_tab_page_ads/new_tab_page_ad_event_viewed.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_info.h"

namespace catsxp_ads {

std::unique_ptr<AdEventInterface<NewTabPageAdInfo>>
NewTabPageAdEventFactory::Build(
    mojom::NewTabPageAdEventType mojom_ad_event_type) {
  switch (mojom_ad_event_type) {
    case mojom::NewTabPageAdEventType::kServedImpression: {
      return std::make_unique<NewTabPageAdEventServed>();
    }

    case mojom::NewTabPageAdEventType::kViewedImpression: {
      return std::make_unique<NewTabPageAdEventViewed>();
    }

    case mojom::NewTabPageAdEventType::kClicked: {
      return std::make_unique<NewTabPageAdEventClicked>();
    }

    case mojom::NewTabPageAdEventType::kInteraction: {
      return std::make_unique<NewTabPageAdEventInteraction>();
    }

    case mojom::NewTabPageAdEventType::kMediaPlay: {
      return std::make_unique<NewTabPageAdEventMediaPlay>();
    }

    case mojom::NewTabPageAdEventType::kMedia25: {
      return std::make_unique<NewTabPageAdEventMedia25>();
    }

    case mojom::NewTabPageAdEventType::kMedia100: {
      return std::make_unique<NewTabPageAdEventMedia100>();
    }
  }
}

}  // namespace catsxp_ads
