/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/conversion_exclusion_rule.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_util.h"

namespace catsxp_ads {

ConversionExclusionRule::ConversionExclusionRule(AdEventList ad_events)
    : ad_events_(std::move(ad_events)) {}

ConversionExclusionRule::~ConversionExclusionRule() = default;

std::string ConversionExclusionRule::GetCacheKey(
    const CreativeAdInfo& creative_ad) const {
  return creative_ad.creative_set_id;
}

bool ConversionExclusionRule::ShouldInclude(
    const CreativeAdInfo& creative_ad) const {
  if (!DoesRespectCreativeSetCap(
          creative_ad, ad_events_, mojom::ConfirmationType::kConversion,
          kShouldExcludeAdIfCreativeSetExceedsConversionCap.Get())) {
    BLOG(1, "creativeSetId " << creative_ad.creative_set_id
                             << " has exceeded the conversions frequency cap");
    return false;
  }

  return true;
}

}  // namespace catsxp_ads
