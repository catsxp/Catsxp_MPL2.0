/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_database_table_util.h"

#include "base/check.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/database/database_column_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads::database::table {

CreativeSetConversionInfo CreativeSetConversionFromMojomRow(
    const mojom::DBRowInfoPtr& mojom_db_row) {
  CHECK(mojom_db_row);
  CHECK_EQ(4U, mojom_db_row->column_values_union.size());

  CreativeSetConversionInfo creative_set_conversion;

  creative_set_conversion.id = ColumnString(mojom_db_row, 0);
  creative_set_conversion.url_pattern = ColumnString(mojom_db_row, 1);
  creative_set_conversion.observation_window =
      base::Days(ColumnInt(mojom_db_row, 2));
  const base::Time expire_at = ColumnTime(mojom_db_row, 3);
  if (!expire_at.is_null()) {
    creative_set_conversion.expire_at = expire_at;
  }

  return creative_set_conversion;
}

}  // namespace catsxp_ads::database::table
