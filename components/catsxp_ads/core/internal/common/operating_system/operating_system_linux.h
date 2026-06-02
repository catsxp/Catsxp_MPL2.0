/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_OPERATING_SYSTEM_OPERATING_SYSTEM_LINUX_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_OPERATING_SYSTEM_OPERATING_SYSTEM_LINUX_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system.h"

namespace catsxp_ads {

class OperatingSystemLinux final : public OperatingSystem {
 public:
  OperatingSystemLinux();

 private:
  // OperatingSystem:
  std::string GetName() const override;
  OperatingSystemType GetType() const override;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_OPERATING_SYSTEM_OPERATING_SYSTEM_LINUX_H_
