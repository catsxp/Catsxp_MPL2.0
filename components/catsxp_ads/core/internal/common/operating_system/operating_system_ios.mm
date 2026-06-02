/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system_ios.h"

namespace catsxp_ads {

namespace {
constexpr char kOperatingSystemName[] = "ios";
}  // namespace

OperatingSystemIos::OperatingSystemIos() = default;

std::string OperatingSystemIos::GetName() const {
  return kOperatingSystemName;
}

OperatingSystemType OperatingSystemIos::GetType() const {
  return OperatingSystemType::kIOS;
}

}  // namespace catsxp_ads
