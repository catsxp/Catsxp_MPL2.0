/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/geographical/subdivision/subdivision_targeting_util.h"

#include "catsxp/components/catsxp_ads/core/public/targeting/geographical/subdivision/supported_subdivisions.h"

namespace catsxp_ads {

bool ShouldTargetSubdivisionCountryCode(const std::string& country_code) {
  return GetSupportedSubdivisions().contains(country_code);
}

bool ShouldTargetSubdivision(const std::string& country_code,
                             const std::string& subdivision) {
  const SupportedSubdivisionMap& supported_subdivisions =
      GetSupportedSubdivisions();

  const auto iter = supported_subdivisions.find(country_code);
  if (iter == supported_subdivisions.cend()) {
    return false;
  }

  const auto& [_, subdivisions] = *iter;

  return subdivisions.contains(subdivision);
}

}  // namespace catsxp_ads
