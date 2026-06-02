/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SEGMENTS_SEGMENT_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SEGMENTS_SEGMENT_UTIL_H_

#include <algorithm>
#include <string>

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"

namespace catsxp_ads {

struct CatalogInfo;

SegmentList GetSegments(const CatalogInfo& catalog);

template <typename T>
SegmentList GetSegments(const T& creative_ads) {
  SegmentList segments;
  segments.reserve(creative_ads.size());

  for (const auto& creative_ad : creative_ads) {
    segments.push_back(creative_ad.segment);
  }

  std::ranges::sort(segments);
  auto to_remove = std::ranges::unique(segments);
  segments.erase(to_remove.begin(), to_remove.end());
  return segments;
}

std::string GetParentSegment(const std::string& segment);
SegmentList GetParentSegments(const SegmentList& segments);

bool HasChildSegment(const std::string& segment);

bool ShouldFilterSegment(const std::string& segment);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SEGMENTS_SEGMENT_UTIL_H_
