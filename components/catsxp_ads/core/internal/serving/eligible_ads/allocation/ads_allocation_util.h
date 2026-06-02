/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ALLOCATION_ADS_ALLOCATION_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ALLOCATION_ADS_ALLOCATION_UTIL_H_

#include <cstdint>
#include <vector>

#include "base/check.h"
#include "base/rand_util.h"

namespace catsxp_ads {

// Chooses a uniformly random ad from `creative_ads`.
template <typename T>
T ChooseCreativeAdAtRandom(const std::vector<T>& creative_ads) {
  CHECK(!creative_ads.empty());

  const uint64_t rand = base::RandGenerator(creative_ads.size());
  return creative_ads.at(rand);
}

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ALLOCATION_ADS_ALLOCATION_UTIL_H_
