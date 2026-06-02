/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_AD_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_AD_INFO_H_

#include <string>
#include <vector>

#include "base/containers/flat_set.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_daypart_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/condition_matcher_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-shared.h"
#include "url/gurl.h"

namespace catsxp_ads {

struct CreativeAdInfo {
  CreativeAdInfo();

  CreativeAdInfo(const CreativeAdInfo&);
  CreativeAdInfo& operator=(const CreativeAdInfo&);

  CreativeAdInfo(CreativeAdInfo&&) noexcept;
  CreativeAdInfo& operator=(CreativeAdInfo&&) noexcept;

  ~CreativeAdInfo();

  bool operator==(const CreativeAdInfo&) const;

  std::string creative_instance_id;
  std::string creative_set_id;
  std::string campaign_id;
  std::string advertiser_id;
  mojom::NewTabPageAdMetricType metric_type =
      mojom::NewTabPageAdMetricType::kUndefined;
  base::Time start_at;
  base::Time end_at;
  int daily_cap = 0;
  int priority = 0;
  double pass_through_rate = 0.0;
  int per_day = 0;
  int per_week = 0;
  int per_month = 0;
  int total_max = 0;
  double value = 0.0;
  std::string segment;
  ConditionMatcherMap condition_matchers;
  CreativeDaypartSet dayparts;
  base::flat_set<std::string> geo_targets;
  GURL target_url;
};

using CreativeAdList = std::vector<CreativeAdInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_AD_INFO_H_
