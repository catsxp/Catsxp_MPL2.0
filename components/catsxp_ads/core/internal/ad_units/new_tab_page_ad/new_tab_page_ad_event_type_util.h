/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_EVENT_TYPE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_EVENT_TYPE_UTIL_H_

#include <optional>
#include <string_view>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

std::optional<mojom::NewTabPageAdEventType> ToMojomNewTabPageAdEventType(
    std::string_view value);

std::string_view ToString(mojom::NewTabPageAdEventType value);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_EVENT_TYPE_UTIL_H_
