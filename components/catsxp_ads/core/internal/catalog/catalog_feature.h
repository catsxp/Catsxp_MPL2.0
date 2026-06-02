/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"
#include "base/time/time.h"

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kCatalogFeature);

inline constexpr base::FeatureParam<base::TimeDelta> kCatalogLifespan{
    &kCatalogFeature, "lifespan", base::Days(1)};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_FEATURE_H_
