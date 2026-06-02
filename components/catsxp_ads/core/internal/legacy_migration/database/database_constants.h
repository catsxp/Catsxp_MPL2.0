/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_DATABASE_DATABASE_CONSTANTS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_DATABASE_DATABASE_CONSTANTS_H_

namespace catsxp_ads::database {

inline constexpr int kVersionNumber = 57;
inline constexpr int kCompatibleVersionNumber = 57;

// If the database version number is less than or equal to this value, the
// database will be razed and recreated during migration. This should be updated
// to match CR versions of the browser that no longer refill confirmation
// tokens.
inline constexpr int kRazeDatabaseThresholdVersionNumber = 32;

}  // namespace catsxp_ads::database

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_DATABASE_DATABASE_CONSTANTS_H_
