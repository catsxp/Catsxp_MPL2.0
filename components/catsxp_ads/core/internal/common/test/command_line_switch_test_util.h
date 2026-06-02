/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_COMMAND_LINE_SWITCH_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_COMMAND_LINE_SWITCH_TEST_UTIL_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/common/test/command_line_switch_test_info.h"

namespace catsxp_ads::test {

// Should only be called from `test::TestBase::SetUpMocks`.
void AppendCommandLineSwitches(
    const CommandLineSwitchList& command_line_switches);

std::string ToString(const CommandLineSwitchInfo& command_line_switch);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_COMMAND_LINE_SWITCH_TEST_UTIL_H_
