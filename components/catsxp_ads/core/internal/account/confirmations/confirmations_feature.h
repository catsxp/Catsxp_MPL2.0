/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATIONS_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATIONS_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace base {
class TimeDelta;
}  // namespace base

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kConfirmationsFeature);

inline constexpr base::FeatureParam<base::TimeDelta>
    kProcessConfirmationInitialBackoffDelay{
        &kConfirmationsFeature, "process_confirmation_initial_backoff_delay",
        base::Seconds(15)};

inline constexpr base::FeatureParam<base::TimeDelta>
    kProcessConfirmationMaxBackoffDelay{
        &kConfirmationsFeature, "process_confirmation_max_backoff_delay",
        base::Hours(6)};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATIONS_FEATURE_H_
