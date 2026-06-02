/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/legacy_migration/confirmations/legacy_confirmation_migration_confirmation_queue_builder.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/queue/queue_item/confirmation_queue_item_builder.h"

namespace catsxp_ads {

ConfirmationQueueItemList BuildConfirmationQueueItems(
    const std::optional<ConfirmationList>& confirmations) {
  if (!confirmations) {
    return {};
  }

  ConfirmationQueueItemList confirmation_queue_items;
  confirmation_queue_items.reserve(confirmations->size());
  for (const auto& confirmation : *confirmations) {
    confirmation_queue_items.push_back(BuildConfirmationQueueItem(
        confirmation, /*process_at=*/base::Time::Now()));
  }
  return confirmation_queue_items;
}

}  // namespace catsxp_ads
