/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/history/ad_history_database_table_util.h"

#include "base/check.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_type.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/ad_type.h"
#include "catsxp/components/catsxp_ads/core/internal/common/database/database_column_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"
#include "url/gurl.h"

namespace catsxp_ads::database::table {

AdHistoryItemInfo AdHistoryItemFromMojomRow(
    const mojom::DBRowInfoPtr& mojom_db_row) {
  CHECK(mojom_db_row);
  CHECK_EQ(12U, mojom_db_row->column_values_union.size());

  AdHistoryItemInfo ad_history_item;

  ad_history_item.created_at = ColumnTime(mojom_db_row, 0);
  ad_history_item.type = ToMojomAdType(ColumnString(mojom_db_row, 1));
  ad_history_item.confirmation_type =
      ToMojomConfirmationType(ColumnString(mojom_db_row, 2));
  ad_history_item.placement_id = ColumnString(mojom_db_row, 3);
  ad_history_item.creative_instance_id = ColumnString(mojom_db_row, 4);
  ad_history_item.creative_set_id = ColumnString(mojom_db_row, 5);
  ad_history_item.campaign_id = ColumnString(mojom_db_row, 6);
  ad_history_item.advertiser_id = ColumnString(mojom_db_row, 7);
  ad_history_item.segment = ColumnString(mojom_db_row, 8);
  ad_history_item.title = ColumnString(mojom_db_row, 9);
  ad_history_item.description = ColumnString(mojom_db_row, 10);
  ad_history_item.target_url = GURL(ColumnString(mojom_db_row, 11));

  return ad_history_item;
}

}  // namespace catsxp_ads::database::table
