/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_OPERATING_SYSTEM_OPERATING_SYSTEM_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_OPERATING_SYSTEM_OPERATING_SYSTEM_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system_types.h"

namespace catsxp_ads {

class OperatingSystem {
 public:
  static const OperatingSystem& GetInstance();

  static void SetForTesting(const OperatingSystem* operating_system);

  OperatingSystem();

  OperatingSystem(const OperatingSystem&) = delete;
  OperatingSystem& operator=(const OperatingSystem&) = delete;

  virtual ~OperatingSystem();

  virtual std::string GetName() const;
  virtual OperatingSystemType GetType() const;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_OPERATING_SYSTEM_OPERATING_SYSTEM_H_
