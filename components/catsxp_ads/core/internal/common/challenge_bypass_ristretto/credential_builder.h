/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_CREDENTIAL_BUILDER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_CREDENTIAL_BUILDER_H_

#include <optional>
#include <string>

#include "base/values.h"

namespace catsxp_ads::cbr {

class UnblindedToken;

std::optional<base::DictValue> MaybeBuildCredential(
    const UnblindedToken& unblinded_token,
    const std::string& payload);

}  // namespace catsxp_ads::cbr

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_CREDENTIAL_BUILDER_H_
