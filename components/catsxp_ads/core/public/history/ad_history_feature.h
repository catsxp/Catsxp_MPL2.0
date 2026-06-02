/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_HISTORY_AD_HISTORY_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_HISTORY_AD_HISTORY_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kAdHistoryFeature);

inline constexpr base::FeatureParam<base::TimeDelta> kAdHistoryRetentionPeriod{
    &kAdHistoryFeature, "retention_period", base::Days(30)};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_HISTORY_AD_HISTORY_FEATURE_H_
