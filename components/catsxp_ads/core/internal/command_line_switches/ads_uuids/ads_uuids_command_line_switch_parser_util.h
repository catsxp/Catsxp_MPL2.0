/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMAND_LINE_SWITCHES_ADS_UUIDS_ADS_UUIDS_COMMAND_LINE_SWITCH_PARSER_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMAND_LINE_SWITCHES_ADS_UUIDS_ADS_UUIDS_COMMAND_LINE_SWITCH_PARSER_UTIL_H_

#include <string>

#include "base/containers/flat_map.h"

namespace catsxp_ads {

base::flat_map<std::string, bool> ParseAdsUuidsCommandLineSwitch();

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMAND_LINE_SWITCHES_ADS_UUIDS_ADS_UUIDS_COMMAND_LINE_SWITCH_PARSER_UTIL_H_
