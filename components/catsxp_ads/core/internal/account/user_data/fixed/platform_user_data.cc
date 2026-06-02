/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/platform_user_data.h"

#include <string>
#include <string_view>

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system.h"

namespace catsxp_ads {

namespace {
constexpr std::string_view kPlatformKey = "platform";
}  // namespace

base::DictValue BuildPlatformUserData() {
  const std::string platform_name = OperatingSystem::GetInstance().GetName();
  if (platform_name.empty()) {
    // Invalid platform name.
    return {};
  }

  return base::DictValue().Set(kPlatformKey, platform_name);
}

}  // namespace catsxp_ads
