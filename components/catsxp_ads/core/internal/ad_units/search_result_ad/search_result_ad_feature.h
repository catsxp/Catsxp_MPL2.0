/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_SEARCH_RESULT_AD_SEARCH_RESULT_AD_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_SEARCH_RESULT_AD_SEARCH_RESULT_AD_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kSearchResultAdFeature);

// Set to 0 to never cap.
inline constexpr base::FeatureParam<size_t> kMaximumSearchResultAdsPerHour{
    &kSearchResultAdFeature, "maximum_ads_per_hour", 0};

// Set to 0 to never cap.
inline constexpr base::FeatureParam<size_t> kMaximumSearchResultAdsPerDay{
    &kSearchResultAdFeature, "maximum_ads_per_day", 0};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_SEARCH_RESULT_AD_SEARCH_RESULT_AD_FEATURE_H_
