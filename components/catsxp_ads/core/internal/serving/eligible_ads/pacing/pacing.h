/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PACING_PACING_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PACING_PACING_H_

#include "base/trace_event/trace_event.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/pacing/pacing_util.h"
#include "catsxp/components/catsxp_ads/core/public/ads_constants.h"

namespace catsxp_ads {

struct CreativeAdInfo;

template <typename T>
void PaceCreativeAds(T& creative_ads) {
  TRACE_EVENT(kTraceEventCategory, "Pacing::PaceCreativeAds", "creative_ads",
              creative_ads.size());

  std::erase_if(creative_ads, [](const CreativeAdInfo& creative_ad) {
    return ShouldPaceAd(creative_ad);
  });
}

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PACING_PACING_H_
