/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SEGMENTS_SEGMENT_TYPES_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SEGMENTS_SEGMENT_TYPES_H_

#include <string>
#include <vector>

#include "base/functional/callback.h"

namespace catsxp_ads {

using SegmentList = std::vector<std::string>;

using BuildSegmentsCallback = base::OnceCallback<void(const SegmentList&)>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SEGMENTS_SEGMENT_TYPES_H_
