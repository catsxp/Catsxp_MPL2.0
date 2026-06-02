/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/environment/environment_flag_util.h"

#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

bool IsProductionEnvironment() {
  return GlobalState::GetInstance()->CommandLineSwitches().environment_type ==
         mojom::EnvironmentType::kProduction;
}

}  // namespace catsxp_ads
