/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_SUBDIVISION_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_SUBDIVISION_UTIL_H_

#include <optional>
#include <string>


namespace catsxp_ads {

std::optional<std::string> GetSubdivisionCountryCode(
    const std::string& subdivision);
std::optional<std::string> GetSubdivisionCode(const std::string& subdivision);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_SUBDIVISION_UTIL_H_
