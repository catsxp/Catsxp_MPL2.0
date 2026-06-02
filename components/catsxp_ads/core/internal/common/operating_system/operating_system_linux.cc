/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system_linux.h"

namespace catsxp_ads {

namespace {
constexpr char kOperatingSystemName[] = "linux";
}  // namespace

OperatingSystemLinux::OperatingSystemLinux() = default;

std::string OperatingSystemLinux::GetName() const {
  return kOperatingSystemName;
}

OperatingSystemType OperatingSystemLinux::GetType() const {
  return OperatingSystemType::kLinux;
}

}  // namespace catsxp_ads
