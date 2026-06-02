/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/did_override/did_override_command_line_flag_util.h"

#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"

namespace catsxp_ads {

bool DidOverrideCommandLine() {
  return GlobalState::GetInstance()
      ->CommandLineSwitches()
      .did_override_from_command_line;
}

}  // namespace catsxp_ads
