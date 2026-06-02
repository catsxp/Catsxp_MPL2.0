/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace base {
class TimeDelta;
}  // namespace base

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kNewTabPageAdFeature);

// Set to 0 to never cap.
inline constexpr base::FeatureParam<size_t> kMaximumNewTabPageAdsPerHour{
    &kNewTabPageAdFeature, "maximum_ads_per_hour", 4};

// Set to 0 to never cap.
inline constexpr base::FeatureParam<size_t> kMaximumNewTabPageAdsPerDay{
    &kNewTabPageAdFeature, "maximum_ads_per_day", 20};

// Set to 0 to never cap.
inline constexpr base::FeatureParam<base::TimeDelta>
    kNewTabPageAdMinimumWaitTime{&kNewTabPageAdFeature, "minimum_wait_time",
                                 base::Minutes(1)};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_FEATURE_H_
