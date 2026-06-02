/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/new_tab_page_ads/new_tab_page_ad_exclusion_rules.h"

#include <memory>

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/grace_period_exclusion_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/anti_targeting/resource/anti_targeting_resource.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/geographical/subdivision/subdivision_targeting.h"

namespace catsxp_ads {

NewTabPageAdExclusionRules::NewTabPageAdExclusionRules(
    const AdEventList& ad_events,
    const SubdivisionTargeting& subdivision_targeting,
    const AntiTargetingResource& anti_targeting_resource,
    const SiteHistoryList& site_history)
    : ExclusionRulesBase(ad_events,
                         subdivision_targeting,
                         anti_targeting_resource,
                         site_history) {
  exclusion_rules_.push_back(std::make_unique<GracePeriodExclusionRule>());
}

NewTabPageAdExclusionRules::~NewTabPageAdExclusionRules() = default;

}  // namespace catsxp_ads
