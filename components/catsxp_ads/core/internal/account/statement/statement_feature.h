/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_STATEMENT_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_STATEMENT_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kAccountStatementFeature);

inline constexpr base::FeatureParam<int> kNextPaymentDay{
    &kAccountStatementFeature, "next_payment_day", 7};

inline constexpr base::FeatureParam<double> kMinEstimatedEarningsMultiplier{
    &kAccountStatementFeature, "minimum_estimated_earnings_multiplier", 0.8};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_STATEMENT_FEATURE_H_
