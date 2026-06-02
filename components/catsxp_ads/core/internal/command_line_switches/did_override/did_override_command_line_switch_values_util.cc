/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/did_override/did_override_command_line_switch_values_util.h"

#include <algorithm>

#include "base/check.h"
#include "base/command_line.h"
#include "components/variations/variations_switches.h"

namespace catsxp_ads {

namespace {

const char* const kSwitches[] = {
    variations::switches::kFakeVariationsChannel,
    variations::switches::kVariationsOverrideCountry};

}  // namespace

bool DidOverrideCommandLineSwitchValues() {
  CHECK(base::CommandLine::InitializedForCurrentProcess());
  const base::CommandLine* const command_line =
      base::CommandLine::ForCurrentProcess();

  return std::ranges::any_of(
      kSwitches, [command_line](const auto* const switch_string) {
        CHECK(switch_string);
        return !command_line->GetSwitchValueASCII(switch_string).empty();
      });
}

}  // namespace catsxp_ads
