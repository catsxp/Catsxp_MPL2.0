/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_NEW_TAB_PAGE_ADS_NEW_TAB_PAGE_AD_PERMISSION_RULES_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_NEW_TAB_PAGE_ADS_NEW_TAB_PAGE_AD_PERMISSION_RULES_H_

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/permission_rules_base.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"

namespace catsxp_ads {

class NewTabPageAdPermissionRules final : public PermissionRulesBase {
 public:
  static bool HasPermission(const AdEventList& ad_events);
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_NEW_TAB_PAGE_ADS_NEW_TAB_PAGE_AD_PERMISSION_RULES_H_
