/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/debug/debug_flag_util.h"

#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"

namespace catsxp_ads {

bool ShouldDebug() {
  return GlobalState::GetInstance()->CommandLineSwitches().should_debug;
}

}  // namespace catsxp_ads
