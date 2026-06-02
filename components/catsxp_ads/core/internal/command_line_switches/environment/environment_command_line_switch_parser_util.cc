/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/environment/environment_command_line_switch_parser_util.h"

#include <utility>

#include "base/notreached.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_rewards/core/rewards_flags.h"

namespace catsxp_ads {

std::optional<mojom::EnvironmentType> ParseEnvironmentCommandLineSwitch() {
  const catsxp_rewards::RewardsFlags& rewards_flags =
      catsxp_rewards::RewardsFlags::ForCurrentProcess();
  if (!rewards_flags.environment) {
    return std::nullopt;
  }

  switch (*rewards_flags.environment) {
    case catsxp_rewards::RewardsFlags::Environment::kDevelopment:
    case catsxp_rewards::RewardsFlags::Environment::kStaging: {
      return mojom::EnvironmentType::kStaging;
    }

    case catsxp_rewards::RewardsFlags::Environment::kProduction: {
      return mojom::EnvironmentType::kProduction;
    }
  }

  NOTREACHED() << "Unexpected value for Environment: "
               << std::to_underlying(*rewards_flags.environment);
}

}  // namespace catsxp_ads
