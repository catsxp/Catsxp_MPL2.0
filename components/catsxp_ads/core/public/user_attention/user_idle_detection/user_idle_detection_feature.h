/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_USER_ATTENTION_USER_IDLE_DETECTION_USER_IDLE_DETECTION_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_USER_ATTENTION_USER_IDLE_DETECTION_USER_IDLE_DETECTION_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace base {
class TimeDelta;
}  // namespace base

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kUserIdleDetectionFeature);

inline constexpr base::FeatureParam<base::TimeDelta>
    kUserIdleDetectionThreshold{&kUserIdleDetectionFeature, "idle_threshold",
                                base::Seconds(5)};

// Set to 0 for infinite idle time.
inline constexpr base::FeatureParam<base::TimeDelta>
    kMaximumUserIdleDetectionTime{&kUserIdleDetectionFeature,
                                  "maximum_idle_time", base::Seconds(0)};

inline constexpr base::FeatureParam<bool> kShouldDetectScreenWasLocked{
    &kUserIdleDetectionFeature, "should_detect_screen_was_locked", false};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_USER_ATTENTION_USER_IDLE_DETECTION_USER_IDLE_DETECTION_FEATURE_H_
