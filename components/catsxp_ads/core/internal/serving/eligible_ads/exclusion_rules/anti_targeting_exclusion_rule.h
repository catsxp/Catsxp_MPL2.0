/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_ANTI_TARGETING_EXCLUSION_RULE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_ANTI_TARGETING_EXCLUSION_RULE_H_

#include <string>

#include "base/memory/raw_ref.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_interface.h"
#include "catsxp/components/catsxp_ads/core/public/history/site_history.h"

namespace catsxp_ads {

class AntiTargetingResource;
struct CreativeAdInfo;

class AntiTargetingExclusionRule final
    : public ExclusionRuleInterface<CreativeAdInfo> {
 public:
  AntiTargetingExclusionRule(const AntiTargetingResource& resource,
                             SiteHistoryList site_history);

  AntiTargetingExclusionRule(const AntiTargetingExclusionRule&) = delete;
  AntiTargetingExclusionRule& operator=(const AntiTargetingExclusionRule&) =
      delete;

  ~AntiTargetingExclusionRule() override;

  // ExclusionRuleInterface:
  std::string GetCacheKey(const CreativeAdInfo& creative_ad) const override;
  bool ShouldInclude(const CreativeAdInfo& creative_ad) const override;

 private:
  bool DoesRespectCap(const CreativeAdInfo& creative_ad) const;

  const raw_ref<const AntiTargetingResource> resource_;

  SiteHistoryList site_history_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_ANTI_TARGETING_EXCLUSION_RULE_H_
