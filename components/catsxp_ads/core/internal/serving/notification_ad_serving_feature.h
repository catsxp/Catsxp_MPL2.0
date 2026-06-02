/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_NOTIFICATION_AD_SERVING_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_NOTIFICATION_AD_SERVING_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kNotificationAdServingFeature);

inline constexpr base::FeatureParam<int> kNotificationAdServingVersion{
    &kNotificationAdServingFeature, "version", 2};

inline constexpr base::FeatureParam<base::TimeDelta>
    kServeFirstNotificationAdAfter{&kNotificationAdServingFeature,
                                   "serve_first_ad_after", base::Minutes(2)};

inline constexpr base::FeatureParam<base::TimeDelta>
    kMinimumDelayBeforeServingNotificationAd{
        &kNotificationAdServingFeature, "minimum_delay_before_serving_an_ad",
        base::Minutes(1)};

inline constexpr base::FeatureParam<base::TimeDelta>
    kRetryServingNotificationAdAfter{&kNotificationAdServingFeature,
                                     "retry_serving_ad_after",
                                     base::Minutes(2)};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_NOTIFICATION_AD_SERVING_FEATURE_H_
