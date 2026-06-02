/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/command_line_permission_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/did_override/did_override_command_line_flag_util.h"
#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/environment/environment_flag_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"

namespace catsxp_ads {

bool HasCommandLinePermission() {
  if (!IsProductionEnvironment()) {
    // Always respect cap for staging environment.
    return true;
  }

  if (!DidOverrideCommandLine()) {
    return true;
  }

  BLOG(2, "Command-line arg is not supported");
  return false;
}

}  // namespace catsxp_ads
