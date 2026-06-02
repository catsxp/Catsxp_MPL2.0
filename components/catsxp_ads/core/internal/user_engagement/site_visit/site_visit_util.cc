/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/site_visit/site_visit_util.h"

#include <utility>

#include "base/notreached.h"
#include "catsxp/components/catsxp_ads/core/internal/application_state/browser_manager.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/internal/tabs/tab_manager.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/common/url/url_util.h"
#include "url/gurl.h"

namespace catsxp_ads {

bool IsAllowedToLandOnPage(mojom::AdType mojom_ad_type) {
  switch (mojom_ad_type) {
    case mojom::AdType::kNewTabPageAd: {
      // Only if:
      // - The user has opted into new tab page ads and has joined Catsxp
      //   Rewards.
      return UserHasOptedInToNewTabPageAds() && UserHasJoinedCatsxpRewards();
    }

    case mojom::AdType::kNotificationAd: {
      // Only if:
      // - The user has opted into notification ads. Users cannot opt into
      //   notification ads without joining Catsxp Rewards.
      return UserHasOptedInToNotificationAds();
    }

    case mojom::AdType::kSearchResultAd: {
      // Only if:
      // - The user has opted into search result ads and has joined Catsxp
      //   Rewards.
      return UserHasJoinedCatsxpRewards() && UserHasOptedInToSearchResultAds();
    }

    case mojom::AdType::kUndefined: {
      break;
    }
  }

  NOTREACHED() << "Unexpected value for mojom::AdType: "
               << std::to_underlying(mojom_ad_type);
}

bool ShouldResumePageLand(int32_t tab_id) {
  return TabManager::GetInstance().IsVisible(tab_id) &&
         BrowserManager::GetInstance().IsActive() &&
         BrowserManager::GetInstance().IsInForeground();
}

bool DidLandOnPage(int32_t tab_id, const GURL& url) {
  std::optional<TabInfo> tab = TabManager::GetInstance().MaybeGetForId(tab_id);
  if (!tab) {
    // The tab has been closed.
    return false;
  }

  return DomainOrHostExists(tab->redirect_chain, url);
}

}  // namespace catsxp_ads
