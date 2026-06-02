/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CONFIRMATIONS_LEGACY_CONFIRMATION_MIGRATION_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CONFIRMATIONS_LEGACY_CONFIRMATION_MIGRATION_H_

#include <optional>

#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads {

struct WalletInfo;

// Parses `kConfirmationsJsonFilename`, writes valid confirmation queue items,
// confirmation tokens, and payment tokens into their respective database
// tables, then deletes the file. If `wallet` is absent only the confirmation
// queue is migrated. If the file does not exist the migration is considered
// complete.
void MigrateConfirmationState(std::optional<WalletInfo> wallet,
                              ResultCallback callback);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CONFIRMATIONS_LEGACY_CONFIRMATION_MIGRATION_H_
