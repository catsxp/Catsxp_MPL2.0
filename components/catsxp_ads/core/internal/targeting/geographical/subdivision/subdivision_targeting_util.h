/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_GEOGRAPHICAL_SUBDIVISION_SUBDIVISION_TARGETING_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_GEOGRAPHICAL_SUBDIVISION_SUBDIVISION_TARGETING_UTIL_H_

#include <string>

namespace catsxp_ads {

bool ShouldTargetSubdivisionCountryCode(const std::string& country_code);

bool ShouldTargetSubdivision(const std::string& country_code,
                             const std::string& subdivision);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_GEOGRAPHICAL_SUBDIVISION_SUBDIVISION_TARGETING_UTIL_H_
