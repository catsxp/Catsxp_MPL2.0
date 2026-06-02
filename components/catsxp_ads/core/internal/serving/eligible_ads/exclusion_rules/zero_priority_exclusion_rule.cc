/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/zero_priority_exclusion_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"

namespace catsxp_ads {

ZeroPriorityExclusionRule::ZeroPriorityExclusionRule() = default;

ZeroPriorityExclusionRule::~ZeroPriorityExclusionRule() = default;

std::string ZeroPriorityExclusionRule::GetCacheKey(
    const CreativeAdInfo& creative_ad) const {
  return creative_ad.creative_instance_id;
}

bool ZeroPriorityExclusionRule::ShouldInclude(
    const CreativeAdInfo& creative_ad) const {
  if (creative_ad.priority == 0) {
    BLOG(1, "creativeInstanceId " << creative_ad.creative_instance_id
                                  << " excluded because priority is 0");
    return false;
  }

  return true;
}

}  // namespace catsxp_ads
