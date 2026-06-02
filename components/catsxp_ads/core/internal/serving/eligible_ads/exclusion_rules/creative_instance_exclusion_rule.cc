/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/creative_instance_exclusion_rule.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

CreativeInstanceExclusionRule::CreativeInstanceExclusionRule(
    AdEventList ad_events)
    : ad_events_(std::move(ad_events)) {}

CreativeInstanceExclusionRule::~CreativeInstanceExclusionRule() = default;

std::string CreativeInstanceExclusionRule::GetCacheKey(
    const CreativeAdInfo& creative_ad) const {
  return creative_ad.creative_instance_id;
}

bool CreativeInstanceExclusionRule::ShouldInclude(
    const CreativeAdInfo& creative_ad) const {
  if (!DoesRespectCreativeCap(
          creative_ad, ad_events_, mojom::ConfirmationType::kServedImpression,
          kShouldExcludeAdIfCreativeInstanceWithinTimeWindow.Get(),
          kShouldExcludeAdIfCreativeInstanceExceedsPerHourCap.Get())) {
    BLOG(1, "creativeInstanceId "
                << creative_ad.creative_instance_id
                << " has exceeded the creative instance frequency cap");
    return false;
  }

  return true;
}

}  // namespace catsxp_ads
