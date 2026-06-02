/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/per_day_exclusion_rule.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_util.h"

namespace catsxp_ads {

PerDayExclusionRule::PerDayExclusionRule(AdEventList ad_events)
    : ad_events_(std::move(ad_events)) {}

PerDayExclusionRule::~PerDayExclusionRule() = default;

std::string PerDayExclusionRule::GetCacheKey(
    const CreativeAdInfo& creative_ad) const {
  return creative_ad.creative_set_id;
}

bool PerDayExclusionRule::ShouldInclude(
    const CreativeAdInfo& creative_ad) const {
  if (!DoesRespectCreativeSetCap(
          creative_ad, ad_events_, mojom::ConfirmationType::kServedImpression,
          /*time_constraint=*/base::Days(1), creative_ad.per_day)) {
    BLOG(1, "creativeSetId " << creative_ad.creative_set_id
                             << " has exceeded the perDay frequency cap");
    return false;
  }

  return true;
}

}  // namespace catsxp_ads
