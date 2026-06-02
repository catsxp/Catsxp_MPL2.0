/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PRIORITY_PRIORITY_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PRIORITY_PRIORITY_H_

#include <cstddef>

#include "base/containers/flat_map.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/priority/priority_util.h"

namespace catsxp_ads {

template <typename T>
using PrioritizedCreativeAdBuckets =
    base::flat_map</*priority*/ int, /*creative_ads*/ T>;

template <typename T>
PrioritizedCreativeAdBuckets<T> SortCreativeAdsIntoBucketsByPriority(
    const T& creative_ads) {
  PrioritizedCreativeAdBuckets<T> buckets;

  for (const auto& creative_ad : creative_ads) {
    buckets[creative_ad.priority].push_back(creative_ad);
  }

  return buckets;
}

template <typename T>
void LogNumberOfCreativeAdsPerBucket(
    const PrioritizedCreativeAdBuckets<T>& buckets) {
  size_t bucket = 1;

  for (const auto& [priority, creative_ads] : buckets) {
    LogNumberOfUntargetedCreativeAdsForBucket(creative_ads, priority, bucket);
    LogNumberOfTargetedCreativeAdsForBucket(creative_ads, priority, bucket);

    ++bucket;
  }
}

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PRIORITY_PRIORITY_H_
