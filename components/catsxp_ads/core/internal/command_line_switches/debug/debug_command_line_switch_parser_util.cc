/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/debug/debug_command_line_switch_parser_util.h"

#include "catsxp/components/catsxp_rewards/core/rewards_flags.h"

namespace catsxp_ads {

bool ParseDebugCommandLineSwitch() {
  return catsxp_rewards::RewardsFlags::ForCurrentProcess().debug;
}

}  // namespace catsxp_ads
