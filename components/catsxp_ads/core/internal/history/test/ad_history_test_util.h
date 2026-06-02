/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_TEST_AD_HISTORY_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_TEST_AD_HISTORY_TEST_UTIL_H_

#include <vector>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"

namespace catsxp_ads::test {

AdHistoryItemInfo BuildAdHistoryItem(
    mojom::AdType mojom_ad_type,
    mojom::ConfirmationType mojom_confirmation_type,
    bool use_random_uuids);

AdHistoryList BuildAdHistory(
    mojom::AdType mojom_ad_type,
    const std::vector<mojom::ConfirmationType>& mojom_confirmation_types,
    bool use_random_uuids);

AdHistoryList BuildAdHistoryForSamePlacement(
    mojom::AdType mojom_ad_type,
    const std::vector<mojom::ConfirmationType>& mojom_confirmation_types,
    bool use_random_uuids);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_TEST_AD_HISTORY_TEST_UTIL_H_
