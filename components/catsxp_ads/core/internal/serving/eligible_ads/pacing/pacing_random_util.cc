/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/pacing/pacing_random_util.h"

#include <optional>

#include "base/check_is_test.h"
#include "base/rand_util.h"

namespace {
std::optional<double> g_pacing_random_number_for_testing;
}  // namespace

namespace catsxp_ads {

double GeneratePacingRandomNumber() {
  if (g_pacing_random_number_for_testing) {
    CHECK_IS_TEST();

    return *g_pacing_random_number_for_testing;
  }

  return base::RandDouble();
}

ScopedPacingRandomNumberSetterForTesting::
    ScopedPacingRandomNumberSetterForTesting(double number) {
  CHECK_IS_TEST();

  g_pacing_random_number_for_testing = number;
}

ScopedPacingRandomNumberSetterForTesting::
    ~ScopedPacingRandomNumberSetterForTesting() {
  g_pacing_random_number_for_testing = std::nullopt;
}

}  // namespace catsxp_ads
