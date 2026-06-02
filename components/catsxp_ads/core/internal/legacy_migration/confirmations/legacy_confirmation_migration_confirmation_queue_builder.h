/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CONFIRMATIONS_LEGACY_CONFIRMATION_MIGRATION_CONFIRMATION_QUEUE_BUILDER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CONFIRMATIONS_LEGACY_CONFIRMATION_MIGRATION_CONFIRMATION_QUEUE_BUILDER_H_

#include <optional>

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/queue/queue_item/confirmation_queue_item_info.h"

namespace catsxp_ads {

// Converts a parsed confirmation list into confirmation queue items for
// database insertion. Returns an empty list if `confirmations` is absent.
ConfirmationQueueItemList BuildConfirmationQueueItems(
    const std::optional<ConfirmationList>& confirmations);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CONFIRMATIONS_LEGACY_CONFIRMATION_MIGRATION_CONFIRMATION_QUEUE_BUILDER_H_
