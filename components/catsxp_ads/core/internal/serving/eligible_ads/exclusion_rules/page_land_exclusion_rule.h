/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_PAGE_LAND_EXCLUSION_RULE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_PAGE_LAND_EXCLUSION_RULE_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_interface.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"

namespace catsxp_ads {

struct CreativeAdInfo;

class PageLandExclusionRule final
    : public ExclusionRuleInterface<CreativeAdInfo> {
 public:
  explicit PageLandExclusionRule(AdEventList ad_events);

  PageLandExclusionRule(const PageLandExclusionRule&) = delete;
  PageLandExclusionRule& operator=(const PageLandExclusionRule&) = delete;

  ~PageLandExclusionRule() override;

  // ExclusionRuleInterface:
  std::string GetCacheKey(const CreativeAdInfo& creative_ad) const override;
  bool ShouldInclude(const CreativeAdInfo& creative_ad) const override;

 private:
  const AdEventList ad_events_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_PAGE_LAND_EXCLUSION_RULE_H_
