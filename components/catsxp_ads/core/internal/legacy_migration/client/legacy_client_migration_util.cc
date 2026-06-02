/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/legacy_migration/client/legacy_client_migration_util.h"

#include "catsxp/components/catsxp_ads/core/internal/prefs/pref_util.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"

namespace catsxp_ads {

bool HasMigratedClientState() {
  return GetProfileBooleanPref(prefs::kHasMigratedClientState);
}

}  // namespace catsxp_ads
