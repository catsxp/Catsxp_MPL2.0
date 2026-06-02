/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_ADS_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_ADS_UTIL_H_

#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

class PrefService;

namespace catsxp_ads {

bool IsStagingEnvironment(PrefService& prefs);

// Determines whether ads are supported in the user's region, returning `true`
// if so, otherwise `false`.
bool IsSupportedRegion();

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_ADS_UTIL_H_
