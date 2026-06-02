/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_ZERO_PRIORITY_EXCLUSION_RULE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_ZERO_PRIORITY_EXCLUSION_RULE_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_interface.h"

namespace catsxp_ads {

struct CreativeAdInfo;

// Excludes creative ads with a priority of 0. Priority-0 ads are never
// servable and must be removed before round-robin so they do not consume
// rotation slots.
class ZeroPriorityExclusionRule final
    : public ExclusionRuleInterface<CreativeAdInfo> {
 public:
  ZeroPriorityExclusionRule();

  ZeroPriorityExclusionRule(const ZeroPriorityExclusionRule&) = delete;
  ZeroPriorityExclusionRule& operator=(const ZeroPriorityExclusionRule&) =
      delete;

  ~ZeroPriorityExclusionRule() override;

  // ExclusionRuleInterface:
  std::string GetCacheKey(const CreativeAdInfo& creative_ad) const override;
  bool ShouldInclude(const CreativeAdInfo& creative_ad) const override;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_ZERO_PRIORITY_EXCLUSION_RULE_H_
