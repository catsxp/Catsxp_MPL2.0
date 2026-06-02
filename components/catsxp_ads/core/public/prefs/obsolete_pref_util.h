/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_PREFS_OBSOLETE_PREF_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_PREFS_OBSOLETE_PREF_UTIL_H_

#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

class PrefRegistrySimple;
class PrefService;

namespace catsxp_ads {

void RegisterProfilePrefsForMigration(PrefRegistrySimple* registry);
void MigrateObsoleteProfilePrefs(PrefService* prefs);

void RegisterLocalStatePrefsForMigration(PrefRegistrySimple* registry);
void MigrateObsoleteLocalStatePrefs(PrefService* local_state);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_PREFS_OBSOLETE_PREF_UTIL_H_
