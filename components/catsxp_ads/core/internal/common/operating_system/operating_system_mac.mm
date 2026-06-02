/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system_mac.h"

namespace catsxp_ads {

namespace {
constexpr char kOperatingSystemName[] = "macos";
}  // namespace

OperatingSystemMac::OperatingSystemMac() = default;

std::string OperatingSystemMac::GetName() const {
  return kOperatingSystemName;
}

OperatingSystemType OperatingSystemMac::GetType() const {
  return OperatingSystemType::kMacOS;
}

}  // namespace catsxp_ads
