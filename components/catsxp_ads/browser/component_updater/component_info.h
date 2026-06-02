/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_COMPONENT_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_COMPONENT_INFO_H_

#include <string_view>

namespace catsxp_ads {

struct ComponentInfo {
  std::string_view id;
  std::string_view public_key_base64;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_COMPONENT_INFO_H_
