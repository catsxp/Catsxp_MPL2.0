/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/per_month_exclusion_rule.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

PerMonthExclusionRule::PerMonthExclusionRule(AdEventList ad_events)
    : ad_events_(std::move(ad_events)) {}

PerMonthExclusionRule::~PerMonthExclusionRule() = default;

std::string PerMonthExclusionRule::GetCacheKey(
    const CreativeAdInfo& creative_ad) const {
  return creative_ad.creative_set_id;
}

bool PerMonthExclusionRule::ShouldInclude(
    const CreativeAdInfo& creative_ad) const {
  if (!DoesRespectCreativeSetCap(
          creative_ad, ad_events_, mojom::ConfirmationType::kServedImpression,
          /*time_constraint=*/base::Days(28), creative_ad.per_month)) {
    BLOG(1, "creativeSetId " << creative_ad.creative_set_id
                             << " has exceeded the perMonth frequency cap");
    return false;
  }

  return true;
}

}  // namespace catsxp_ads
