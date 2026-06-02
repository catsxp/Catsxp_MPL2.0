/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transactions_database_table_util.h"

#include "base/check.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_type.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/ad_type.h"
#include "catsxp/components/catsxp_ads/core/internal/common/database/database_column_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads::database::table {

TransactionInfo TransactionFromMojomRow(
    const mojom::DBRowInfoPtr& mojom_db_row) {
  CHECK(mojom_db_row);
  CHECK_EQ(8U, mojom_db_row->column_values_union.size());

  TransactionInfo transaction;

  transaction.id = ColumnString(mojom_db_row, 0);

  const base::Time created_at = ColumnTime(mojom_db_row, 1);
  if (!created_at.is_null()) {
    transaction.created_at = created_at;
  }

  transaction.creative_instance_id = ColumnString(mojom_db_row, 2);
  transaction.value = ColumnDouble(mojom_db_row, 3);
  transaction.segment = ColumnString(mojom_db_row, 4);
  transaction.ad_type = ToMojomAdType(ColumnString(mojom_db_row, 5));
  transaction.confirmation_type =
      ToMojomConfirmationType(ColumnString(mojom_db_row, 6));

  const base::Time reconciled_at = ColumnTime(mojom_db_row, 7);
  if (!reconciled_at.is_null()) {
    transaction.reconciled_at = reconciled_at;
  }

  return transaction;
}

}  // namespace catsxp_ads::database::table
