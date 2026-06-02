/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system.h"
#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system_types.h"

namespace catsxp_ads {

bool IsMobile() {
  const OperatingSystemType type = OperatingSystem::GetInstance().GetType();
  return type == OperatingSystemType::kAndroid ||
         type == OperatingSystemType::kIOS;
}

}  // namespace catsxp_ads
