/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_TRANSACTION_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_TRANSACTION_UTIL_H_

#include <string>
#include <vector>

#include "base/location.h"
#include "catsxp/components/catsxp_ads/core/internal/common/database/database_transaction_callback.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads::database {

// Returns true if the transaction result is a success.
bool IsTransactionSuccessful(
    const mojom::DBTransactionResultInfoPtr& mojom_db_transaction_result);

// Run a database transaction. The callback takes one argument -
// `mojom::DBTransactionResultInfoPtr` containing the info of the transaction.
void RunTransaction(const base::Location& location,
                    mojom::DBTransactionInfoPtr mojom_db_transaction,
                    RunDBTransactionCallback callback);

// Run a database transaction.
void RunTransaction(const base::Location& location,
                    mojom::DBTransactionInfoPtr mojom_db_transaction,
                    ResultCallback callback);

// Raze the database. This must be done before any other actions are run. All
// tables must be recreated after the raze operation is completed.
void Raze(const mojom::DBTransactionInfoPtr& mojom_db_transaction);

// Execute a SQL statement.
void Execute(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
             const std::string& sql);

// Execute a SQL statement with placeholders.
void Execute(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
             const std::string& sql,
             const std::vector<std::string>& subst);

// Vacuum the database. This must be done after any other actions are run.
void Vacuum(const mojom::DBTransactionInfoPtr& mojom_db_transaction);

}  // namespace catsxp_ads::database

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_TRANSACTION_UTIL_H_
