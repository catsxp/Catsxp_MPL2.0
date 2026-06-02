/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_ADS_SUMMARY_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_ADS_SUMMARY_UTIL_H_

#include <cstdint>

#include "base/containers/flat_map.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace base {
class Time;
}  // namespace base

namespace catsxp_ads {

base::flat_map<mojom::AdType, /*count*/ int32_t> GetAdsSummaryForDateRange(
    const TransactionList& transactions,
    base::Time from_time,
    base::Time to_time);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_ADS_SUMMARY_UTIL_H_
