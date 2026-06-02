/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_SEGMENTS_TOP_USER_MODEL_SEGMENTS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_SEGMENTS_TOP_USER_MODEL_SEGMENTS_H_

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"

namespace catsxp_ads {

struct UserModelInfo;

SegmentList GetTopChildSegments(const UserModelInfo& user_model);
SegmentList GetTopParentSegments(const UserModelInfo& user_model);

SegmentList GetTopChildInterestSegments(const UserModelInfo& user_model);
SegmentList GetTopParentInterestSegments(const UserModelInfo& user_model);

SegmentList GetTopChildLatentInterestSegments(const UserModelInfo& user_model);
SegmentList GetTopParentLatentInterestSegments(const UserModelInfo& user_model);

SegmentList GetTopChildIntentSegments(const UserModelInfo& user_model);
SegmentList GetTopParentIntentSegments(const UserModelInfo& user_model);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_SEGMENTS_TOP_USER_MODEL_SEGMENTS_H_
