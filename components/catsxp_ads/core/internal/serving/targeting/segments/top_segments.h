/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_SEGMENTS_TOP_SEGMENTS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_SEGMENTS_TOP_SEGMENTS_H_

#include <cstddef>
#include <optional>
#include <string>

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"

namespace catsxp_ads {

SegmentList GetTopSegments(const SegmentList& segments,
                           size_t max_count,
                           bool parent_only);

std::optional<std::string> GetTopSegment(const SegmentList& segments,
                                         bool parent_only);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_SEGMENTS_TOP_SEGMENTS_H_
