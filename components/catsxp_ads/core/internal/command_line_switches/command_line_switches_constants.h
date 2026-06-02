/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMAND_LINE_SWITCHES_COMMAND_LINE_SWITCHES_CONSTANTS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMAND_LINE_SWITCHES_COMMAND_LINE_SWITCHES_CONSTANTS_H_

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-shared.h"
#include "build/build_config.h"

namespace catsxp_ads {

#if defined(OFFICIAL_BUILD)
inline constexpr mojom::EnvironmentType kDefaultEnvironmentType =
    mojom::EnvironmentType::kProduction;
#else   // OFFICIAL_BUILD
inline constexpr mojom::EnvironmentType kDefaultEnvironmentType =
    mojom::EnvironmentType::kStaging;
#endif  // !OFFICIAL_BUILD

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMAND_LINE_SWITCHES_COMMAND_LINE_SWITCHES_CONSTANTS_H_
