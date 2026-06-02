/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PRIORITY_PRIORITY_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PRIORITY_PRIORITY_UTIL_H_

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_util.h"

namespace catsxp_ads {

template <typename T>
void LogNumberOfUntargetedCreativeAdsForBucket(const T& creative_ads,
                                               int priority,
                                               size_t bucket) {
  const size_t count = UntargetedCreativeAdCount(creative_ads);
  if (count > 0) {
    BLOG(3, count << " untargeted ads with a priority of " << priority
                  << " in bucket " << bucket);
  }
}

template <typename T>
void LogNumberOfTargetedCreativeAdsForBucket(const T& creative_ads,
                                             int priority,
                                             size_t bucket) {
  const size_t count = TargetedCreativeAdCount(creative_ads);
  if (count > 0) {
    BLOG(3, count << " targeted ads with a priority of " << priority
                  << " in bucket " << bucket);
  }
}

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PRIORITY_PRIORITY_UTIL_H_
