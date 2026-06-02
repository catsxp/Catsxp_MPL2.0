/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_events_database_table_util.h"

#include "base/check.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_type.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/ad_type.h"
#include "catsxp/components/catsxp_ads/core/internal/common/database/database_column_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "url/gurl.h"

namespace catsxp_ads::database::table {

AdEventInfo AdEventFromMojomRow(const mojom::DBRowInfoPtr& mojom_db_row) {
  CHECK(mojom_db_row);
  CHECK_EQ(10U, mojom_db_row->column_values_union.size());

  AdEventInfo ad_event;

  ad_event.placement_id = ColumnString(mojom_db_row, 0);
  ad_event.type = ToMojomAdType(ColumnString(mojom_db_row, 1));
  ad_event.confirmation_type =
      ToMojomConfirmationType(ColumnString(mojom_db_row, 2));
  ad_event.campaign_id = ColumnString(mojom_db_row, 3);
  ad_event.creative_set_id = ColumnString(mojom_db_row, 4);
  ad_event.creative_instance_id = ColumnString(mojom_db_row, 5);
  ad_event.advertiser_id = ColumnString(mojom_db_row, 6);
  ad_event.segment = ColumnString(mojom_db_row, 7);
  ad_event.target_url = GURL(ColumnString(mojom_db_row, 8));
  const base::Time created_at = ColumnTime(mojom_db_row, 9);
  if (!created_at.is_null()) {
    ad_event.created_at = created_at;
  }

  return ad_event;
}

}  // namespace catsxp_ads::database::table
