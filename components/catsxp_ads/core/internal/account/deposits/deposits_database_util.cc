/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/deposits/deposits_database_util.h"

#include "base/functional/bind.h"
#include "catsxp/components/catsxp_ads/core/internal/account/deposits/deposits_database_table.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"

namespace catsxp_ads::database {

void PurgeExpiredDeposits() {
  const table::Deposits database_table;
  database_table.PurgeExpired(base::BindOnce([](bool success) {
    if (!success) {
      return BLOG(0, "Failed to purge expired deposits");
    }

    BLOG(3, "Successfully purged expired deposits");
  }));
}

}  // namespace catsxp_ads::database
