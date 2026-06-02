/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/daily_cap_exclusion_rule.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

DailyCapExclusionRule::DailyCapExclusionRule(AdEventList ad_events)
    : ad_events_(std::move(ad_events)) {}

DailyCapExclusionRule::~DailyCapExclusionRule() = default;

std::string DailyCapExclusionRule::GetCacheKey(
    const CreativeAdInfo& creative_ad) const {
  return creative_ad.campaign_id;
}

bool DailyCapExclusionRule::ShouldInclude(
    const CreativeAdInfo& creative_ad) const {
  if (!DoesRespectCampaignCap(creative_ad, ad_events_,
                              mojom::ConfirmationType::kServedImpression,
                              base::Days(1), creative_ad.daily_cap)) {
    BLOG(1, "campaignId " << creative_ad.campaign_id
                          << " has exceeded the dailyCap frequency cap");
    return false;
  }

  return true;
}

}  // namespace catsxp_ads
