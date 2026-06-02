/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_QUEUE_ITEM_TEST_CONFIRMATION_QUEUE_ITEM_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_QUEUE_ITEM_TEST_CONFIRMATION_QUEUE_ITEM_TEST_UTIL_H_

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/queue/queue_item/confirmation_queue_item_info.h"

namespace catsxp_ads {

struct ConfirmationInfo;

namespace test {

ConfirmationQueueItemList BuildConfirmationQueueItems(
    const ConfirmationInfo& confirmation,
    size_t count);

void SaveConfirmationQueueItems(
    const ConfirmationQueueItemList& confirmation_queue_items);

void BuildAndSaveConfirmationQueueItems(const ConfirmationInfo& confirmation,
                                        size_t count);

}  // namespace test

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_QUEUE_ITEM_TEST_CONFIRMATION_QUEUE_ITEM_TEST_UTIL_H_
