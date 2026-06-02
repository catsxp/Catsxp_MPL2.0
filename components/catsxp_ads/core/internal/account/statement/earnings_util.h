/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_EARNINGS_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_EARNINGS_UTIL_H_

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"

namespace catsxp_ads {

double GetUnreconciledEarnings(const TransactionList& transactions);
double GetReconciledEarningsForThisMonth(const TransactionList& transactions);
double GetReconciledEarningsForPreviousMonth(
    const TransactionList& transactions);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_EARNINGS_UTIL_H_
