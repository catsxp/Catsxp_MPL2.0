/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/command_line_switch_test_util_internal.h"

#include "catsxp/components/catsxp_rewards/core/rewards_flags.h"

namespace catsxp_ads::test {

void SimulateCommandLineSwitches() {
  catsxp_rewards::RewardsFlags::SetForceParsingForTesting(true);
}

void ResetCommandLineSwitches() {
  catsxp_rewards::RewardsFlags::SetForceParsingForTesting(false);
}

std::optional<bool>& DidAppendCommandLineSwitches() {
  static std::optional<bool> did_append;
  return did_append;
}

}  // namespace catsxp_ads::test
