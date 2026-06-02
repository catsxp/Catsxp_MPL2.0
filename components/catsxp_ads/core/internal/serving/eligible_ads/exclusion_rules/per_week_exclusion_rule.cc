/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/per_week_exclusion_rule.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

PerWeekExclusionRule::PerWeekExclusionRule(AdEventList ad_events)
    : ad_events_(std::move(ad_events)) {}

PerWeekExclusionRule::~PerWeekExclusionRule() = default;

std::string PerWeekExclusionRule::GetCacheKey(
    const CreativeAdInfo& creative_ad) const {
  return creative_ad.creative_set_id;
}

bool PerWeekExclusionRule::ShouldInclude(
    const CreativeAdInfo& creative_ad) const {
  if (!DoesRespectCreativeSetCap(
          creative_ad, ad_events_, mojom::ConfirmationType::kServedImpression,
          /*time_constraint=*/base::Days(7), creative_ad.per_week)) {
    BLOG(1, "creativeSetId " << creative_ad.creative_set_id
                             << " has exceeded the perWeek frequency cap");
    return false;
  }

  return true;
}

}  // namespace catsxp_ads
