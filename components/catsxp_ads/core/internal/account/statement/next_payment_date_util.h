/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_NEXT_PAYMENT_DATE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_NEXT_PAYMENT_DATE_UTIL_H_

#include <optional>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"

namespace catsxp_ads {

std::optional<base::Time> MaybeCalculateNextPaymentDate(
    base::Time next_payment_token_redemption_at,
    const TransactionList& transactions);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_NEXT_PAYMENT_DATE_UTIL_H_
