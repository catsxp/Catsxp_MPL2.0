/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_FEATURE_H_

#include <string>

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace base {
class TimeDelta;
}  // namespace base

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kUserActivityFeature);

inline constexpr base::FeatureParam<size_t> kMaximumUserActivityEvents{
    &kUserActivityFeature, "maximum_events", 3600};

inline constexpr base::FeatureParam<std::string> kUserActivityTriggers{
    &kUserActivityFeature, "triggers",
    "0D0B14110D0B14110D0B14110D0B1411=-1.0;0D0B1411070707=-1.0;07070707=-1.0"};

inline constexpr base::FeatureParam<base::TimeDelta> kUserActivityTimeWindow{
    &kUserActivityFeature, "time_window", base::Minutes(15)};

inline constexpr base::FeatureParam<double> kUserActivityThreshold{
    &kUserActivityFeature, "threshold", 0.0};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_FEATURE_H_
