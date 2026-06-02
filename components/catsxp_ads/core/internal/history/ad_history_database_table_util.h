/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_DATABASE_TABLE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_DATABASE_TABLE_UTIL_H_

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"

namespace catsxp_ads::database::table {

AdHistoryItemInfo AdHistoryItemFromMojomRow(
    const mojom::DBRowInfoPtr& mojom_db_row);

}  // namespace catsxp_ads::database::table

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_DATABASE_TABLE_UTIL_H_
