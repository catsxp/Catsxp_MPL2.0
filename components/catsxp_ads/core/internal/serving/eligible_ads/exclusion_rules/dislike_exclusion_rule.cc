/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/dislike_exclusion_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/ads_core/ads_core_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/reactions/reactions.h"

namespace catsxp_ads {

namespace {

bool DoesRespectCap(const CreativeAdInfo& creative_ad) {
  return GetReactions().AdReactionTypeForId(creative_ad.advertiser_id) !=
         mojom::ReactionType::kDisliked;
}

}  // namespace

std::string DislikeExclusionRule::GetCacheKey(
    const CreativeAdInfo& creative_ad) const {
  return creative_ad.advertiser_id;
}

bool DislikeExclusionRule::ShouldInclude(
    const CreativeAdInfo& creative_ad) const {
  if (!DoesRespectCap(creative_ad)) {
    BLOG(1, "advertiserId " << creative_ad.advertiser_id
                            << " excluded due to being disliked");
    return false;
  }

  return true;
}

}  // namespace catsxp_ads
