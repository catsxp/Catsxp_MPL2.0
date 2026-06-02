/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_NOTIFICATION_AD_SERVING_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_NOTIFICATION_AD_SERVING_UTIL_H_

namespace base {
class Time;
class TimeDelta;
}  // namespace base

namespace catsxp_ads {

bool ShouldServeAdsAtRegularIntervals();

void SetServeAdAt(base::Time serve_ad_at);
base::Time ServeAdAt();

base::TimeDelta CalculateDelayBeforeServingAnAd();

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_NOTIFICATION_AD_SERVING_UTIL_H_
