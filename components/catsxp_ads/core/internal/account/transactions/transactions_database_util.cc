/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transactions_database_util.h"

#include "base/functional/bind.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transactions_database_table.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"

namespace catsxp_ads::database {

void PurgeExpiredTransactions() {
  const table::Transactions database_table;
  database_table.PurgeExpired(base::BindOnce([](bool success) {
    if (!success) {
      return BLOG(0, "Failed to purge expired transactions");
    }

    BLOG(3, "Successfully purged expired transactions");
  }));
}

void SaveTransactions(const TransactionList& transactions) {
  table::Transactions database_table;
  database_table.Save(transactions, base::BindOnce([](bool success) {
                        if (!success) {
                          return BLOG(0, "Failed to save transactions");
                        }

                        BLOG(3, "Successfully saved transactions");
                      }));
}

}  // namespace catsxp_ads::database
