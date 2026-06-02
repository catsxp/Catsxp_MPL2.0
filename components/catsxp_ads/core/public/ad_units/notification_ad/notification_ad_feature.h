/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/notification_ad/notification_ad_constants.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kNotificationAdFeature);

// Ad notification timeout in seconds. Set to 0 to never time out
inline constexpr base::FeatureParam<base::TimeDelta> kNotificationAdTimeout{
    &kNotificationAdFeature, "notification_ad_timeout",
    kDefaultNotificationAdTimeout};

inline constexpr base::FeatureParam<int> kDefaultNotificationAdsPerHour{
    &kNotificationAdFeature, "default_ads_per_hour",
    kDefaultCatsxpRewardsNotificationAdsPerHour};

// Set to 0 to never cap.
inline constexpr base::FeatureParam<size_t> kMaximumNotificationAdsPerDay{
    &kNotificationAdFeature, "maximum_ads_per_day", 100};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_FEATURE_H_
