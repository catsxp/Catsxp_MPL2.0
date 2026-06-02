/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_idle_detection/user_idle_detection_util.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/public/user_attention/user_idle_detection/user_idle_detection_feature.h"

namespace catsxp_ads {

bool MaybeScreenWasLocked(bool screen_was_locked) {
  return kShouldDetectScreenWasLocked.Get() && screen_was_locked;
}

bool HasExceededMaximumIdleTime(base::TimeDelta idle_time) {
  const base::TimeDelta maximum_idle_time = kMaximumUserIdleDetectionTime.Get();
  return maximum_idle_time.is_positive() && idle_time > maximum_idle_time;
}

}  // namespace catsxp_ads
