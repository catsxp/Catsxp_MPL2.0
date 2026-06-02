/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/database/database_table_interface.h"

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/legacy_migration/database/database_constants.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads::database {

void TableInterface::Migrate(
    const mojom::DBTransactionInfoPtr& mojom_db_transaction,
    int to_version) {
  CHECK(mojom_db_transaction);

  if (to_version == kVersionNumber) {
    Create(mojom_db_transaction);
  }
}

}  // namespace catsxp_ads::database
