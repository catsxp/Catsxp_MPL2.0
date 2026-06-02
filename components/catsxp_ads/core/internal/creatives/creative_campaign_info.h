/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_CAMPAIGN_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_CAMPAIGN_INFO_H_

#include <string>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-shared.h"

namespace catsxp_ads {

struct CreativeCampaignInfo final {
  mojom::NewTabPageAdMetricType metric_type =
      mojom::NewTabPageAdMetricType::kUndefined;
  base::Time start_at;
  base::Time end_at;
  int daily_cap = 0;
  std::string advertiser_id;
  int priority = 0;
  double pass_through_rate = 0.0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_CAMPAIGN_INFO_H_
