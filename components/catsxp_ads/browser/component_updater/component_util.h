/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_COMPONENT_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_COMPONENT_UTIL_H_

#include <optional>
#include <string_view>

#include "catsxp/components/catsxp_ads/browser/component_updater/component_info.h"

namespace catsxp_ads {

std::optional<ComponentInfo> GetComponent(std::string_view id);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_COMPONENT_UTIL_H_
