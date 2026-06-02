/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/random/test/scoped_rand_time_delta_with_jitter_for_testing.h"

namespace catsxp_ads::test {

ScopedRandTimeDeltaWithJitterForTesting::
    ScopedRandTimeDeltaWithJitterForTesting(base::TimeDelta time_delta) {
  SetRandTimeDeltaWithJitterForTesting(time_delta);
}

ScopedRandTimeDeltaWithJitterForTesting::
    ~ScopedRandTimeDeltaWithJitterForTesting() {
  SetRandTimeDeltaWithJitterForTesting(std::nullopt);
}

}  // namespace catsxp_ads::test
