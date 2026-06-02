/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_QUEUE_ITEM_CONFIRMATION_QUEUE_ITEM_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_QUEUE_ITEM_CONFIRMATION_QUEUE_ITEM_INFO_H_

#include <optional>
#include <vector>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_info.h"

namespace catsxp_ads {

struct ConfirmationQueueItemInfo final {
  ConfirmationQueueItemInfo();

  ConfirmationQueueItemInfo(const ConfirmationQueueItemInfo&);
  ConfirmationQueueItemInfo& operator=(const ConfirmationQueueItemInfo&);

  ConfirmationQueueItemInfo(ConfirmationQueueItemInfo&&) noexcept;
  ConfirmationQueueItemInfo& operator=(ConfirmationQueueItemInfo&&) noexcept;

  ~ConfirmationQueueItemInfo();

  bool operator==(const ConfirmationQueueItemInfo&) const = default;

  [[nodiscard]] bool IsValid() const;

  ConfirmationInfo confirmation;
  std::optional<base::Time> process_at;
  int retry_count = 0;
};

using ConfirmationQueueItemList = std::vector<ConfirmationQueueItemInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_QUEUE_ITEM_CONFIRMATION_QUEUE_ITEM_INFO_H_
