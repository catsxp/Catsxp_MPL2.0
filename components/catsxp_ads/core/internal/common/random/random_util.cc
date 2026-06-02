/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/random/random_util.h"

#include <optional>

#include "base/check_is_test.h"
#include "base/rand_util.h"
#include "base/time/time.h"

namespace catsxp_ads {

namespace {

constexpr double kMinRandomFactor = 0.5;

std::optional<base::TimeDelta> g_rand_time_delta_with_jitter_for_testing;

}  // namespace

base::TimeDelta RandTimeDeltaWithJitter(base::TimeDelta time_delta) {
  if (g_rand_time_delta_with_jitter_for_testing) {
    CHECK_IS_TEST();

    return *g_rand_time_delta_with_jitter_for_testing;
  }

  const double random_factor = kMinRandomFactor + base::RandDouble();

  return base::Seconds(time_delta.InSecondsF() * random_factor);
}

void SetRandTimeDeltaWithJitterForTesting(  // IN-TEST
    std::optional<base::TimeDelta> value) {
  CHECK_IS_TEST();

  g_rand_time_delta_with_jitter_for_testing = value;
}

}  // namespace catsxp_ads
