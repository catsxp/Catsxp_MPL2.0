/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_TARGETING_GEOGRAPHICAL_SUBDIVISION_SUPPORTED_SUBDIVISIONS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_TARGETING_GEOGRAPHICAL_SUBDIVISION_SUPPORTED_SUBDIVISIONS_H_

#include <string_view>

#include "base/containers/flat_map.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

using SubdivisionMap = base::flat_map</*subdivision*/ std::string_view,
                                      /*name*/ std::string_view>;

using SupportedSubdivisionMap =
    base::flat_map</*country_code*/ std::string_view, SubdivisionMap>;

const SupportedSubdivisionMap& GetSupportedSubdivisions();

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_TARGETING_GEOGRAPHICAL_SUBDIVISION_SUPPORTED_SUBDIVISIONS_H_
