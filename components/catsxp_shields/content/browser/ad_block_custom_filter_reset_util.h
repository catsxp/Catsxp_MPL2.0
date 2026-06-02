/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_AD_BLOCK_CUSTOM_FILTER_RESET_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_AD_BLOCK_CUSTOM_FILTER_RESET_UTIL_H_

#include <optional>
#include <string>

namespace catsxp_shields {

std::optional<std::string> ResetCustomFiltersForHost(
    std::string_view host,
    std::string_view custom_filters);

bool IsCustomFiltersAvailable(std::string_view host,
                              std::string_view custom_filters);

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_AD_BLOCK_CUSTOM_FILTER_RESET_UTIL_H_
