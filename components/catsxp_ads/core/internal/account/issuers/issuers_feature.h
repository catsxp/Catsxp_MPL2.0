/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kIssuersFeature);

inline constexpr base::FeatureParam<size_t> kMaximumTokenIssuerPublicKeys{
    &kIssuersFeature, "maximum_token_issuer_public_keys", 6};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_FEATURE_H_
