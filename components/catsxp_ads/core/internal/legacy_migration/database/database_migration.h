/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_DATABASE_DATABASE_MIGRATION_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_DATABASE_DATABASE_MIGRATION_H_

#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads::database {

void MigrateFromVersion(int from_version, ResultCallback callback);

}  // namespace catsxp_ads::database

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_DATABASE_DATABASE_MIGRATION_H_
