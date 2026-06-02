/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/segments_database_table.h"

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/common/database/database_table_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/database/database_transaction_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads::database::table {


void Segments::Create(const mojom::DBTransactionInfoPtr& mojom_db_transaction) {
  CHECK(mojom_db_transaction);

  Execute(mojom_db_transaction, R"(
      CREATE TABLE segments (
        creative_set_id TEXT NOT NULL,
        segment TEXT NOT NULL,
        PRIMARY KEY (
          creative_set_id,
          segment
        ) ON CONFLICT REPLACE
      ))");
}

void Segments::Migrate(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                       int to_version) {
  CHECK(mojom_db_transaction);

  switch (to_version) {
    case 48: {
      MigrateToV48(mojom_db_transaction);
      break;
    }

    default: {
      // No migration needed.
      break;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

void Segments::MigrateToV48(
    const mojom::DBTransactionInfoPtr& mojom_db_transaction) {
  CHECK(mojom_db_transaction);

  // It is safe to recreate the table because it will be repopulated after
  // downloading the catalog post-migration. However, after this migration, we
  // should not drop the table as it will store catalog and non-catalog ad units
  // and maintain relationships with other tables.
  DropTable(mojom_db_transaction, "segments");
  Execute(mojom_db_transaction, R"(
      CREATE TABLE segments (
        creative_set_id TEXT NOT NULL,
        segment TEXT NOT NULL,
        PRIMARY KEY (
          creative_set_id,
          segment
        ) ON CONFLICT REPLACE
      ))");
}

}  // namespace catsxp_ads::database::table
