/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_SEGMENTS_TOP_USER_MODEL_SEGMENTS_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_SEGMENTS_TOP_USER_MODEL_SEGMENTS_UTIL_H_

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"

namespace catsxp_ads {

struct UserModelInfo;

SegmentList GetTopSegments(const UserModelInfo& user_model,
                           size_t max_count,
                           bool parent_only);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_SEGMENTS_TOP_USER_MODEL_SEGMENTS_UTIL_H_
