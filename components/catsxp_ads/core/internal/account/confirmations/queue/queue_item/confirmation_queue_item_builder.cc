/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/queue/queue_item/confirmation_queue_item_builder.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/queue/queue_item/confirmation_queue_item_info.h"

namespace catsxp_ads {

ConfirmationQueueItemInfo BuildConfirmationQueueItem(
    const ConfirmationInfo& confirmation,
    base::Time process_at) {
  ConfirmationQueueItemInfo confirmation_queue_item;
  confirmation_queue_item.confirmation = confirmation;
  confirmation_queue_item.process_at = process_at;

  return confirmation_queue_item;
}

}  // namespace catsxp_ads
