/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system_android.h"

namespace catsxp_ads {

namespace {
constexpr char kOperatingSystemName[] = "android";
}  // namespace

OperatingSystemAndroid::OperatingSystemAndroid() = default;

std::string OperatingSystemAndroid::GetName() const {
  return kOperatingSystemName;
}

OperatingSystemType OperatingSystemAndroid::GetType() const {
  return OperatingSystemType::kAndroid;
}

}  // namespace catsxp_ads
