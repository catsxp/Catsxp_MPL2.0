/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_TOKENS_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_TOKENS_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kAccountTokensFeature);

inline constexpr base::FeatureParam<size_t> kMinConfirmationTokens{
    &kAccountTokensFeature, "minimum_confirmation_tokens", 20};

inline constexpr base::FeatureParam<size_t> kMaxConfirmationTokens{
    &kAccountTokensFeature, "maximum_confirmation_tokens", 50};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_TOKENS_FEATURE_H_
