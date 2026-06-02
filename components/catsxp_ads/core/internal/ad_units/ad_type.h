/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_AD_TYPE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_AD_TYPE_H_

#include <string_view>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

// Returns a `mojom::AdType` value based on the string input.
mojom::AdType ToMojomAdType(std::string_view value);

// Returns a string constant for a given `mojom::AdType` value.
std::string_view ToString(mojom::AdType value);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_AD_TYPE_H_
