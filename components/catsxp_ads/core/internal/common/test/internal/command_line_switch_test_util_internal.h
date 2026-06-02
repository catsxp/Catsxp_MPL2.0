/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_COMMAND_LINE_SWITCH_TEST_UTIL_INTERNAL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_COMMAND_LINE_SWITCH_TEST_UTIL_INTERNAL_H_

#include <optional>

namespace catsxp_ads::test {

void SimulateCommandLineSwitches();
void ResetCommandLineSwitches();

std::optional<bool>& DidAppendCommandLineSwitches();

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_COMMAND_LINE_SWITCH_TEST_UTIL_INTERNAL_H_
