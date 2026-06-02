/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_SUBDIVISION_TARGETING_EXCLUSION_RULE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_SUBDIVISION_TARGETING_EXCLUSION_RULE_H_

#include <string>

#include "base/memory/raw_ref.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_interface.h"

namespace catsxp_ads {

class SubdivisionTargeting;
struct CreativeAdInfo;

class SubdivisionTargetingExclusionRule final
    : public ExclusionRuleInterface<CreativeAdInfo> {
 public:
  explicit SubdivisionTargetingExclusionRule(
      const SubdivisionTargeting& subdivision_targeting);

  SubdivisionTargetingExclusionRule(const SubdivisionTargetingExclusionRule&) =
      delete;
  SubdivisionTargetingExclusionRule& operator=(
      const SubdivisionTargetingExclusionRule&) = delete;

  ~SubdivisionTargetingExclusionRule() override;

  // ExclusionRuleInterface:
  std::string GetCacheKey(const CreativeAdInfo& creative_ad) const override;
  bool ShouldInclude(const CreativeAdInfo& creative_ad) const override;

 private:
  bool DoesRespectCap(const CreativeAdInfo& creative_ad) const;

  const raw_ref<const SubdivisionTargeting> subdivision_targeting_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_SUBDIVISION_TARGETING_EXCLUSION_RULE_H_
