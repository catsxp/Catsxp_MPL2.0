/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_EXCLUSION_RULES_BASE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_EXCLUSION_RULES_BASE_H_

#include <memory>
#include <set>
#include <string>
#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_interface.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/public/history/site_history.h"

namespace catsxp_ads {

class AntiTargetingResource;
class SubdivisionTargeting;
struct CreativeAdInfo;

class ExclusionRulesBase {
 public:
  ExclusionRulesBase(const ExclusionRulesBase&) = delete;
  ExclusionRulesBase& operator=(const ExclusionRulesBase&) = delete;

  virtual ~ExclusionRulesBase();

  virtual bool ShouldExcludeCreativeAd(const CreativeAdInfo& creative_ad);

 protected:
  ExclusionRulesBase(const AdEventList& ad_events,
                     const SubdivisionTargeting& subdivision_targeting,
                     const AntiTargetingResource& anti_targeting_resource,
                     const SiteHistoryList& site_history);

  std::vector<std::unique_ptr<ExclusionRuleInterface<CreativeAdInfo>>>
      exclusion_rules_;

 private:
  bool IsCached(const CreativeAdInfo& creative_ad) const;
  void Cache(const std::string& key);

  std::set</*key*/ std::string> cache_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_EXCLUSION_RULES_BASE_H_
