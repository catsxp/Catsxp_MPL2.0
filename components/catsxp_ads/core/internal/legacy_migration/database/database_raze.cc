/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/legacy_migration/database/database_raze.h"

#include <utility>

#include "base/location.h"
#include "catsxp/components/catsxp_ads/core/internal/common/database/database_transaction_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads::database {

void Raze(ResultCallback callback) {
  mojom::DBTransactionInfoPtr mojom_db_transaction =
      mojom::DBTransactionInfo::New();
  Raze(mojom_db_transaction);

  RunTransaction(FROM_HERE, std::move(mojom_db_transaction),
                 std::move(callback));
}

}  // namespace catsxp_ads::database
