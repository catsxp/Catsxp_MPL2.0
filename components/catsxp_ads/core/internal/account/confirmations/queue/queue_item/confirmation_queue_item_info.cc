/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/queue/queue_item/confirmation_queue_item_info.h"

namespace catsxp_ads {

ConfirmationQueueItemInfo::ConfirmationQueueItemInfo() = default;

ConfirmationQueueItemInfo::ConfirmationQueueItemInfo(
    const ConfirmationQueueItemInfo& other) = default;

ConfirmationQueueItemInfo& ConfirmationQueueItemInfo::operator=(
    const ConfirmationQueueItemInfo& other) = default;

ConfirmationQueueItemInfo::ConfirmationQueueItemInfo(
    ConfirmationQueueItemInfo&& other) noexcept = default;

ConfirmationQueueItemInfo& ConfirmationQueueItemInfo::operator=(
    ConfirmationQueueItemInfo&& other) noexcept = default;

ConfirmationQueueItemInfo::~ConfirmationQueueItemInfo() = default;

bool ConfirmationQueueItemInfo::IsValid() const {
  return !!process_at;
}

}  // namespace catsxp_ads
