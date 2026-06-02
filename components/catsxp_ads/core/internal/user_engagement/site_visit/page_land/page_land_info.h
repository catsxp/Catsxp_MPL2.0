/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_PAGE_LAND_PAGE_LAND_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_PAGE_LAND_PAGE_LAND_INFO_H_

#include <optional>

#include "base/timer/timer.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/ad_info.h"

namespace catsxp_ads {

struct PageLandInfo {
  AdInfo ad;
  base::RetainingOneShotTimer timer;
  std::optional<base::TimeDelta> remaining_time;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_PAGE_LAND_PAGE_LAND_INFO_H_
