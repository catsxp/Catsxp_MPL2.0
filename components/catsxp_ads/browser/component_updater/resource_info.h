/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_INFO_H_

#include <cstdint>
#include <string>

#include "base/files/file_path.h"

namespace catsxp_ads {

struct ResourceInfo {
  std::string id;
  uint16_t version;
  base::FilePath path;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_INFO_H_
