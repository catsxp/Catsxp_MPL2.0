/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ACTIVE_CAMPAIGNS_FILTER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ACTIVE_CAMPAIGNS_FILTER_H_

#include <vector>  // IWYU pragma: keep

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"

namespace catsxp_ads {

// Remove creative ads whose campaign start/end window no longer contains `now`.
// The SQLite query embeds `now` at query time. If significant time passes
// before the callback runs (e.g., due to a system sleep/wake cycle), a campaign
// may have expired in the interim, causing the SQLite `BETWEEN` filter to pass
// with a stale `now` while the campaign is no longer active.
template <typename T>
void FilterInactiveCampaignCreativeAds(T& creative_ads) {
  const base::Time now = base::Time::Now();
  std::erase_if(creative_ads, [&now](const auto& creative_ad) {
    if (now < creative_ad.start_at || now > creative_ad.end_at) {
      BLOG(1, "creativeInstanceId " << creative_ad.creative_instance_id
                                    << " excluded due to campaign being "
                                       "inactive");
      return true;
    }
    return false;
  });
}

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ACTIVE_CAMPAIGNS_FILTER_H_
