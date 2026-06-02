/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_AD_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_AD_UTIL_H_

#include <algorithm>
#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/segments/segment_constants.h"

namespace catsxp_ads {

template <typename T>
size_t UntargetedCreativeAdCount(const T& creative_ads) {
  return std::ranges::count_if(
      creative_ads, [](const CreativeAdInfo& creative_ad) {
        return creative_ad.segment == kUntargetedSegment;
      });
}

template <typename T>
size_t TargetedCreativeAdCount(const T& creative_ads) {
  return std::ranges::count_if(
      creative_ads, [](const CreativeAdInfo& creative_ad) {
        return creative_ad.segment != kUntargetedSegment;
      });
}

template <typename T>
T DeduplicateCreativeAds(const T& creative_ads) {
  T unique_creative_ads = creative_ads;

  std::sort(unique_creative_ads.begin(), unique_creative_ads.end(),
            [](const CreativeAdInfo& lhs, const CreativeAdInfo& rhs) {
              return lhs.creative_instance_id < rhs.creative_instance_id;
            });

  auto to_remove =
      std::unique(unique_creative_ads.begin(), unique_creative_ads.end(),
                  [](const CreativeAdInfo& lhs, const CreativeAdInfo& rhs) {
                    return lhs.creative_instance_id == rhs.creative_instance_id;
                  });
  unique_creative_ads.erase(to_remove, unique_creative_ads.cend());

  return unique_creative_ads;
}

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_AD_UTIL_H_
