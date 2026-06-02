/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PACING_PACING_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PACING_PACING_UTIL_H_

#include <ios>

#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/pacing/pacing_random_util.h"

namespace catsxp_ads {

// Checks if an ad should be paced based on a randomly generated number and the
// ad's pass-through rate. If the random number is less than the pass-through
// rate, the ad is not paced. Otherwise, it is paced.
template <typename T>
bool ShouldPaceAd(const T& ad) {
  const double rand = GeneratePacingRandomNumber();
  if (rand < ad.pass_through_rate) {
    return false;
  }

  BLOG(2, std::fixed << "Pacing delivery for creative instance id "
                     << ad.creative_instance_id << " [Roll("
                     << ad.pass_through_rate << "):" << rand << "]");

  return true;
}

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PACING_PACING_UTIL_H_
