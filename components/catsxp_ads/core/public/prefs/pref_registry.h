/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_PREFS_PREF_REGISTRY_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_PREFS_PREF_REGISTRY_H_

#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

class PrefRegistrySimple;

namespace catsxp_ads {

void RegisterLocalStatePrefs(PrefRegistrySimple* registry);

void RegisterProfilePrefs(PrefRegistrySimple* registry);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_PREFS_PREF_REGISTRY_H_
