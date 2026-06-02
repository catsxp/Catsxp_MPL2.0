/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_LEGACY_MIGRATION_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_LEGACY_MIGRATION_UTIL_H_

#include <string>

namespace catsxp_ads {

// Removes the file with the given `name` from persistent storage. Used to
// remove legacy JSON files after their contents have been migrated to the
// database.
void MaybeDeleteFile(const std::string& name);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_LEGACY_MIGRATION_UTIL_H_
