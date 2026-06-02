/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/command_line_switches/command_line_switches_util.h"

#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/ads_uuids/ads_uuids_command_line_switch_parser_util.h"
#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/command_line_switches_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/debug/debug_command_line_switch_parser_util.h"
#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/did_override/did_override_command_line_switch_values_util.h"
#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/did_override/did_override_command_line_switches_util.h"
#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/did_override/did_override_features_from_command_line_util.h"
#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/environment/environment_command_line_switch_parser_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

namespace {

mojom::EnvironmentType ChooseEnvironmentType() {
  return ParseEnvironmentCommandLineSwitch().value_or(kDefaultEnvironmentType);
}

}  // namespace

mojom::CommandLineSwitchesPtr BuildCommandLineSwitches() {
  mojom::CommandLineSwitchesPtr mojom_command_line_switches =
      mojom::CommandLineSwitches::New();

  mojom_command_line_switches->should_debug = ParseDebugCommandLineSwitch();

  mojom_command_line_switches->did_override_from_command_line =
      DidOverrideFeaturesFromCommandLine() ||
      DidOverrideCommandLineSwitchValues() || DidOverrideCommandLineSwitches();

  mojom_command_line_switches->environment_type = ChooseEnvironmentType();

  mojom_command_line_switches->ads_uuids = ParseAdsUuidsCommandLineSwitch();

  return mojom_command_line_switches;
}

}  // namespace catsxp_ads
