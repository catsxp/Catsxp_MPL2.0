/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/test_environment_util_internal.h"

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/command_line_switch_test_util_internal.h"
#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/command_line_switches/command_line_switches_util.h"

namespace catsxp_ads::test {

void SetUpCommandLineSwitches() {
  CHECK(GlobalState::HasInstance());

  GlobalState::GetInstance()->CommandLineSwitches() =
      *BuildCommandLineSwitches();

  if (!DidAppendCommandLineSwitches()) {
    // Force the test environment to staging if we did not append command-line
    // switches in `SetUpMocks`, or if the test environment does not support
    // passing command-line switches.
    GlobalState::GetInstance()->CommandLineSwitches().environment_type =
        mojom::EnvironmentType::kStaging;
  }
}

void SetUpContentSettings() {
  GlobalState::GetInstance()->ContentSettings().allow_javascript = true;
}

}  // namespace catsxp_ads::test
