/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/test/command_line_switch_test_info.h"

#include <utility>

namespace catsxp_ads::test {

CommandLineSwitchInfo::CommandLineSwitchInfo() = default;

CommandLineSwitchInfo::CommandLineSwitchInfo(std::string key, std::string value)
    : key(std::move(key)), value(std::move(value)) {}

}  // namespace catsxp_ads::test
