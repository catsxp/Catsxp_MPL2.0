/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/segments/top_user_model_segments_util.h"

#include "base/containers/extend.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/segments/top_segments.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/user_model_info.h"

namespace catsxp_ads {

SegmentList GetTopSegments(const UserModelInfo& user_model,
                           size_t max_count,
                           bool parent_only) {
  SegmentList segments;
  segments.reserve(3 * max_count);

  base::Extend(segments, GetTopSegments(user_model.intent.segments, max_count,
                                        parent_only));

  base::Extend(segments, GetTopSegments(user_model.latent_interest.segments,
                                        max_count, parent_only));

  base::Extend(segments, GetTopSegments(user_model.interest.segments, max_count,
                                        parent_only));

  return segments;
}

}  // namespace catsxp_ads
