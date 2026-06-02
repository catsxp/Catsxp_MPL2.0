/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_QUEUE_ITEM_CONFIRMATION_QUEUE_ITEM_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_QUEUE_ITEM_CONFIRMATION_QUEUE_ITEM_UTIL_H_

namespace base {
class TimeDelta;
}  // namespace base

namespace catsxp_ads {

struct ConfirmationInfo;
struct ConfirmationQueueItemInfo;

base::TimeDelta CalculateDelayBeforeProcessingConfirmationQueueItem(
    const ConfirmationQueueItemInfo& confirmation_queue_item);

class ScopedDelayBeforeProcessingConfirmationQueueItemForTesting final {
 public:
  explicit ScopedDelayBeforeProcessingConfirmationQueueItemForTesting(
      base::TimeDelta delay);

  ScopedDelayBeforeProcessingConfirmationQueueItemForTesting(
      const ScopedDelayBeforeProcessingConfirmationQueueItemForTesting&) =
      delete;
  ScopedDelayBeforeProcessingConfirmationQueueItemForTesting& operator=(
      const ScopedDelayBeforeProcessingConfirmationQueueItemForTesting&) =
      delete;

  ~ScopedDelayBeforeProcessingConfirmationQueueItemForTesting();
};

ConfirmationInfo RebuildConfirmationWithoutDynamicUserData(
    const ConfirmationInfo& confirmation);

ConfirmationInfo RebuildConfirmationDynamicUserData(
    const ConfirmationInfo& confirmation);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_QUEUE_ITEM_CONFIRMATION_QUEUE_ITEM_UTIL_H_
