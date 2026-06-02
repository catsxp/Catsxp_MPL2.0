/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/eligible_ads_feature.h"

namespace catsxp_ads {

BASE_FEATURE(kEligibleAdFeature,
             "EligibleAds",
             base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace catsxp_ads
