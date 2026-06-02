/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/reconciled_transactions_util.h"

#include <algorithm>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/time/time_util.h"

namespace catsxp_ads {

namespace {

bool HasReconciledTransactionsForDateRange(const TransactionList& transactions,
                                           base::Time from_time,
                                           base::Time to_time) {
  return std::ranges::any_of(
      transactions, [from_time, to_time](const TransactionInfo& transaction) {
        return DidReconcileTransactionWithinDateRange(transaction, from_time,
                                                      to_time);
      });
}

}  // namespace

bool DidReconcileTransaction(const TransactionInfo& transaction) {
  return !!transaction.reconciled_at;
}

bool DidReconcileTransactionsPreviousMonth(
    const TransactionList& transactions) {
  const base::Time from_time = LocalTimeAtBeginningOfPreviousMonth();
  const base::Time to_time = LocalTimeAtEndOfPreviousMonth();

  return HasReconciledTransactionsForDateRange(transactions, from_time,
                                               to_time);
}

bool DidReconcileTransactionsThisMonth(const TransactionList& transactions) {
  const base::Time from_time = LocalTimeAtBeginningOfThisMonth();
  const base::Time to_time = LocalTimeAtEndOfThisMonth();

  return HasReconciledTransactionsForDateRange(transactions, from_time,
                                               to_time);
}

bool DidReconcileTransactionWithinDateRange(const TransactionInfo& transaction,
                                            base::Time from_time,
                                            base::Time to_time) {
  if (!DidReconcileTransaction(transaction)) {
    return false;
  }

  if (transaction.reconciled_at < from_time ||
      transaction.reconciled_at > to_time) {
    return false;
  }

  return true;
}

}  // namespace catsxp_ads
