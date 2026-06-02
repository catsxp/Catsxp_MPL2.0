/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_SERVICE_HELPER_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_SERVICE_HELPER_H_

#include <optional>
#include <string>

namespace catsxp_shields {

void MergeCspDirectiveInto(std::optional<std::string> from,
                           std::optional<std::string>* into);

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_SERVICE_HELPER_H_
