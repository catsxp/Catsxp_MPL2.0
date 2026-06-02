/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/did_override/did_override_command_line_switches_util.h"

#include <algorithm>
#include <array>
#include <string_view>

#include "base/check.h"
#include "base/command_line.h"

namespace catsxp_ads {

namespace {
constexpr auto kSwitches =
    std::to_array<std::string_view>({"enable-automation"});
}  // namespace

bool DidOverrideCommandLineSwitches() {
  CHECK(base::CommandLine::InitializedForCurrentProcess());
  const base::CommandLine* const command_line =
      base::CommandLine::ForCurrentProcess();

  return std::ranges::any_of(kSwitches, [command_line](auto switch_string) {
    return command_line->HasSwitch(switch_string);
  });
}

}  // namespace catsxp_ads
