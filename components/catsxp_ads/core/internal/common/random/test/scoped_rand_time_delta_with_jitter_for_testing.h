/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_RANDOM_TEST_SCOPED_RAND_TIME_DELTA_WITH_JITTER_FOR_TESTING_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_RANDOM_TEST_SCOPED_RAND_TIME_DELTA_WITH_JITTER_FOR_TESTING_H_

#include <optional>

#include "base/time/time.h"

namespace catsxp_ads {

// Sets the value returned by `RandTimeDeltaWithJitter` for testing. Pass
// `std::nullopt` to restore the default behavior.
void SetRandTimeDeltaWithJitterForTesting(std::optional<base::TimeDelta> value);

}  // namespace catsxp_ads

namespace catsxp_ads::test {

// Overrides the value returned by `RandTimeDeltaWithJitter` for the duration
// of the test, restoring the original behavior upon destruction.
class ScopedRandTimeDeltaWithJitterForTesting final {
 public:
  explicit ScopedRandTimeDeltaWithJitterForTesting(base::TimeDelta time_delta);

  ScopedRandTimeDeltaWithJitterForTesting(
      const ScopedRandTimeDeltaWithJitterForTesting&) = delete;
  ScopedRandTimeDeltaWithJitterForTesting& operator=(
      const ScopedRandTimeDeltaWithJitterForTesting&) = delete;

  ~ScopedRandTimeDeltaWithJitterForTesting();
};

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_RANDOM_TEST_SCOPED_RAND_TIME_DELTA_WITH_JITTER_FOR_TESTING_H_
