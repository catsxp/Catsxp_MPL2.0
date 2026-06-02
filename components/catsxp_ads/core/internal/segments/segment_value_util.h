/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SEGMENTS_SEGMENT_VALUE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SEGMENTS_SEGMENT_VALUE_UTIL_H_

#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"

namespace catsxp_ads {

base::ListValue SegmentsToList(const SegmentList& segments);
SegmentList SegmentsFromList(const base::ListValue& list);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SEGMENTS_SEGMENT_VALUE_UTIL_H_
