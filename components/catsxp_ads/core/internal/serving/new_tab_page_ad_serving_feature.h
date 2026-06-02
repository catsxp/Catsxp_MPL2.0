/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_NEW_TAB_PAGE_AD_SERVING_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_NEW_TAB_PAGE_AD_SERVING_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kNewTabPageAdServingFeature);

inline constexpr base::FeatureParam<int> kNewTabPageAdServingVersion{
    &kNewTabPageAdServingFeature, "version", 2};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_NEW_TAB_PAGE_AD_SERVING_FEATURE_H_
