/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_NOTIFICATION_ADS_NOTIFICATION_AD_EXCLUSION_RULES_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_NOTIFICATION_ADS_NOTIFICATION_AD_EXCLUSION_RULES_H_

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rules_base.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/public/history/site_history.h"

namespace catsxp_ads {

class AntiTargetingResource;
class SubdivisionTargeting;

class NotificationAdExclusionRules final : public ExclusionRulesBase {
 public:
  NotificationAdExclusionRules(
      const AdEventList& ad_events,
      const SubdivisionTargeting& subdivision_targeting,
      const AntiTargetingResource& anti_targeting_resource,
      const SiteHistoryList& site_history);

  NotificationAdExclusionRules(const NotificationAdExclusionRules&) = delete;
  NotificationAdExclusionRules& operator=(const NotificationAdExclusionRules&) =
      delete;

  ~NotificationAdExclusionRules() override;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_NOTIFICATION_ADS_NOTIFICATION_AD_EXCLUSION_RULES_H_
