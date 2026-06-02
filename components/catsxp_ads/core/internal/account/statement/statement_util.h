/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_STATEMENT_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_STATEMENT_UTIL_H_

#include <cstdint>
#include <optional>
#include <utility>

#include "base/containers/flat_map.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

std::optional<base::Time> MaybeGetNextPaymentDate(
    const TransactionList& transactions);

std::pair</*range_low*/ double, /*range_high*/ double>
GetEstimatedEarningsForThisMonth(const TransactionList& transactions);

std::pair</*range_low*/ double, /*range_high*/ double>
GetEstimatedEarningsForPreviousMonth(const TransactionList& transactions);

int32_t GetAdsReceivedThisMonth(const TransactionList& transactions);

base::flat_map<mojom::AdType, /*count*/ int32_t> GetAdsSummaryThisMonth(
    const TransactionList& transactions);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_STATEMENT_UTIL_H_
