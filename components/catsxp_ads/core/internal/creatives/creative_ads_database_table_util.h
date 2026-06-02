/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_ADS_DATABASE_TABLE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_ADS_DATABASE_TABLE_UTIL_H_

#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads::database::table {

CreativeAdInfo CreativeAdFromMojomRow(const mojom::DBRowInfoPtr& mojom_db_row);

// Appends SQL actions to insert `creative_ads` into the `creative_ads` table.
void InsertCreativeAds(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                       const CreativeAdList& creative_ads);

}  // namespace catsxp_ads::database::table

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_ADS_DATABASE_TABLE_UTIL_H_
