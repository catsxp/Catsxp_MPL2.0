/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_ADS_RECEIVED_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_ADS_RECEIVED_UTIL_H_

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"

namespace base {
class Time;
}  // namespace base

namespace catsxp_ads {

size_t GetAdsReceivedForDateRange(const TransactionList& transactions,
                                  base::Time from_time,
                                  base::Time to_time);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_ADS_RECEIVED_UTIL_H_
