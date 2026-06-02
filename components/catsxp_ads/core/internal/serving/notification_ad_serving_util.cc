/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/notification_ad_serving_util.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system_util.h"
#include "catsxp/components/catsxp_ads/core/internal/prefs/pref_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/notification_ad_serving_feature.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"

namespace catsxp_ads {

namespace {

bool HasPreviouslyServedAnAd() {
  return HasProfilePrefPath(prefs::kServeAdAt);
}

base::TimeDelta DelayBeforeServingAnAd() {
  return ServeAdAt() - base::Time::Now();
}

bool ShouldHaveServedAdInThePast() {
  return DelayBeforeServingAnAd().is_negative();
}

bool ShouldServeAd() {
  return base::Time::Now() >= ServeAdAt();
}

}  // namespace

bool ShouldServeAdsAtRegularIntervals() {
  return IsMobile();
}

void SetServeAdAt(base::Time serve_ad_at) {
  SetProfileTimePref(prefs::kServeAdAt, serve_ad_at);
}

base::Time ServeAdAt() {
  return GetProfileTimePref(prefs::kServeAdAt);
}

base::TimeDelta CalculateDelayBeforeServingAnAd() {
  if (!HasPreviouslyServedAnAd()) {
    return kServeFirstNotificationAdAfter.Get();
  }

  if (ShouldHaveServedAdInThePast() || ShouldServeAd()) {
    return kMinimumDelayBeforeServingNotificationAd.Get();
  }

  const base::TimeDelta delay = DelayBeforeServingAnAd();
  if (delay < kMinimumDelayBeforeServingNotificationAd.Get()) {
    return kMinimumDelayBeforeServingNotificationAd.Get();
  }

  return delay;
}

}  // namespace catsxp_ads
