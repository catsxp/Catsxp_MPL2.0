/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_ANTI_TARGETING_ANTI_TARGETING_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_ANTI_TARGETING_ANTI_TARGETING_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kAntiTargetingFeature);

inline constexpr base::FeatureParam<int> kAntiTargetingResourceVersion{
    &kAntiTargetingFeature, "resource_version", 1};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_ANTI_TARGETING_ANTI_TARGETING_FEATURE_H_
