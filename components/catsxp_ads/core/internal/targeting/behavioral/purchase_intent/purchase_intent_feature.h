/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_PURCHASE_INTENT_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_PURCHASE_INTENT_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace base {
class TimeDelta;
}  // namespace base

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kPurchaseIntentFeature);

inline constexpr base::FeatureParam<int> kPurchaseIntentResourceVersion{
    &kPurchaseIntentFeature, "resource_version", 1};

inline constexpr base::FeatureParam<base::TimeDelta> kPurchaseIntentTimeWindow{
    &kPurchaseIntentFeature, "time_window", base::Days(7)};

inline constexpr base::FeatureParam<int> kPurchaseIntentSignalLevel{
    &kPurchaseIntentFeature, "signal_level", 1};

inline constexpr base::FeatureParam<int> kPurchaseIntentThreshold{
    &kPurchaseIntentFeature, "threshold", 3};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_PURCHASE_INTENT_FEATURE_H_
