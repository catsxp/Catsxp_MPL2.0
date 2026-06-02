/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_COMMAND_LINE_SWITCH_TEST_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_COMMAND_LINE_SWITCH_TEST_INFO_H_

#include <string>
#include <vector>

namespace catsxp_ads::test {

struct CommandLineSwitchInfo final {
  CommandLineSwitchInfo();
  CommandLineSwitchInfo(std::string key, std::string value);

  std::string key;
  std::string value;
};

using CommandLineSwitchList = std::vector<CommandLineSwitchInfo>;

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_COMMAND_LINE_SWITCH_TEST_INFO_H_
