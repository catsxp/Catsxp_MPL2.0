/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_COMMAND_LINE_SWITCHES_COMMAND_LINE_SWITCHES_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_COMMAND_LINE_SWITCHES_COMMAND_LINE_SWITCHES_UTIL_H_

#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

// Builds CommandLineSwitches based on command line arguments and environment.
mojom::CommandLineSwitchesPtr BuildCommandLineSwitches();

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_COMMAND_LINE_SWITCHES_COMMAND_LINE_SWITCHES_UTIL_H_
