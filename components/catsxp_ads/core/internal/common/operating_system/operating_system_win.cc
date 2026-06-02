/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system_win.h"

namespace catsxp_ads {

namespace {
constexpr char kOperatingSystemName[] = "windows";
}  // namespace

OperatingSystemWin::OperatingSystemWin() = default;

std::string OperatingSystemWin::GetName() const {
  return kOperatingSystemName;
}

OperatingSystemType OperatingSystemWin::GetType() const {
  return OperatingSystemType::kWindows;
}

}  // namespace catsxp_ads
