/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ELIGIBLE_ADS_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ELIGIBLE_ADS_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kEligibleAdFeature);

inline constexpr base::FeatureParam<int> kSiteHistoryMaxCount{
    &kEligibleAdFeature, "site_history_max_count", 5'000};

inline constexpr base::FeatureParam<int> kSiteHistoryRecentDayRange{
    &kEligibleAdFeature, "site_history_recent_day_range", 180};

inline constexpr base::FeatureParam<bool> kShouldRoundRobin{
    &kEligibleAdFeature, "should_round_robin", true};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ELIGIBLE_ADS_FEATURE_H_
