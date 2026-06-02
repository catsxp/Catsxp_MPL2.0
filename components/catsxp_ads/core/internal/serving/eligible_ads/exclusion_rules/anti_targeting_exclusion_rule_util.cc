/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/anti_targeting_exclusion_rule_util.h"

#include <algorithm>

#include "catsxp/components/catsxp_ads/core/public/common/url/url_util.h"

namespace catsxp_ads {

bool HasVisitedAntiTargetedSites(const SiteHistoryList& site_history,
                                 const AntiTargetingSiteList& sites) {
  return std::ranges::find_first_of(site_history, sites, SameDomainOrHost) !=
         site_history.cend();
}

}  // namespace catsxp_ads
