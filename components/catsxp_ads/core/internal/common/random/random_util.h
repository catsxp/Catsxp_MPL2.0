/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_RANDOM_RANDOM_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_RANDOM_RANDOM_UTIL_H_

// Jitters a time delta by a random factor in [0.5, 1.5). Used to prevent
// thundering-herd effects when scheduling ads-related timers.

namespace base {
class TimeDelta;
}  // namespace base

namespace catsxp_ads {

base::TimeDelta RandTimeDeltaWithJitter(base::TimeDelta time_delta);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_RANDOM_RANDOM_UTIL_H_
