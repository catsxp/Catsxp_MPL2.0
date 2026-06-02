/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/test/fake_operating_system.h"

#include <ostream>  // IWYU pragma: keep
#include <utility>

#include "base/notreached.h"

namespace catsxp_ads {

namespace {

constexpr char kUnknownOperatingSystemName[] = "unknown";
constexpr char kAndroidOperatingSystemName[] = "android";
constexpr char kIOSOperatingSystemName[] = "ios";
constexpr char kLinuxOperatingSystemName[] = "linux";
constexpr char kMacOSOperatingSystemName[] = "macos";
constexpr char kWindowsOperatingSystemName[] = "windows";

}  // namespace

FakeOperatingSystem::FakeOperatingSystem() {
  OperatingSystem::SetForTesting(this);
}

FakeOperatingSystem::~FakeOperatingSystem() {
  OperatingSystem::SetForTesting(nullptr);
}

void FakeOperatingSystem::SetType(OperatingSystemType type) {
  type_ = type;
}

std::string FakeOperatingSystem::GetName() const {
  switch (type_) {
    case OperatingSystemType::kUnknown:
      return kUnknownOperatingSystemName;
    case OperatingSystemType::kAndroid:
      return kAndroidOperatingSystemName;
    case OperatingSystemType::kIOS:
      return kIOSOperatingSystemName;
    case OperatingSystemType::kLinux:
      return kLinuxOperatingSystemName;
    case OperatingSystemType::kMacOS:
      return kMacOSOperatingSystemName;
    case OperatingSystemType::kWindows:
      return kWindowsOperatingSystemName;
  }
  NOTREACHED() << "Unexpected value for OperatingSystemType: "
               << std::to_underlying(type_);
}

OperatingSystemType FakeOperatingSystem::GetType() const {
  return type_;
}

}  // namespace catsxp_ads
