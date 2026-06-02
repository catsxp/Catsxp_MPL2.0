/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMAND_LINE_SWITCHES_ENVIRONMENT_ENVIRONMENT_COMMAND_LINE_SWITCH_PARSER_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMAND_LINE_SWITCHES_ENVIRONMENT_ENVIRONMENT_COMMAND_LINE_SWITCH_PARSER_UTIL_H_

#include <optional>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

std::optional<mojom::EnvironmentType> ParseEnvironmentCommandLineSwitch();

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMAND_LINE_SWITCHES_ENVIRONMENT_ENVIRONMENT_COMMAND_LINE_SWITCH_PARSER_UTIL_H_
