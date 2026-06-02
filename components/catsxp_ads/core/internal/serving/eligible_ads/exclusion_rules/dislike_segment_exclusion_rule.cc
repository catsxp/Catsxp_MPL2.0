/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/dislike_segment_exclusion_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/segments/segment_util.h"

namespace catsxp_ads {

namespace {

bool DoesRespectCap(const CreativeAdInfo& creative_ad) {
  return !ShouldFilterSegment(creative_ad.segment);
}

}  // namespace

std::string DislikeSegmentExclusionRule::GetCacheKey(
    const CreativeAdInfo& creative_ad) const {
  return creative_ad.segment;
}

bool DislikeSegmentExclusionRule::ShouldInclude(
    const CreativeAdInfo& creative_ad) const {
  if (!DoesRespectCap(creative_ad)) {
    BLOG(1, "creativeSetId " << creative_ad.creative_set_id
                             << " excluded due to " << creative_ad.segment
                             << " segment being marked to no "
                                "longer receive ads");
    return false;
  }

  return true;
}

}  // namespace catsxp_ads
