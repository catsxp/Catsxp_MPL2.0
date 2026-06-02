/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_RECONCILED_TRANSACTIONS_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_RECONCILED_TRANSACTIONS_UTIL_H_

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"

namespace base {
class Time;
}  // namespace base

namespace catsxp_ads {

bool DidReconcileTransaction(const TransactionInfo& transaction);
bool DidReconcileTransactionsPreviousMonth(const TransactionList& transactions);
bool DidReconcileTransactionsThisMonth(const TransactionList& transactions);
bool DidReconcileTransactionWithinDateRange(const TransactionInfo& transaction,
                                            base::Time from_time,
                                            base::Time to_time);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_RECONCILED_TRANSACTIONS_UTIL_H_
