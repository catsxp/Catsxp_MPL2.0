/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTIONS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTIONS_H_

#include <string>

#include "base/functional/callback.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace base {
class Time;
}  // namespace base

namespace catsxp_ads {

using AddTransactionCallback =
    base::OnceCallback<void(bool success, const TransactionInfo& transaction)>;

using GetTransactionsCallback =
    base::OnceCallback<void(bool success, const TransactionList& transactions)>;

TransactionInfo BuildTransaction(
    const std::string& creative_instance_id,
    const std::string& segment,
    double value,
    mojom::AdType mojom_ad_type,
    mojom::ConfirmationType mojom_confirmation_type);

TransactionInfo AddTransaction(const std::string& creative_instance_id,
                               const std::string& segment,
                               double value,
                               mojom::AdType mojom_ad_type,
                               mojom::ConfirmationType mojom_confirmation_type,
                               AddTransactionCallback callback);

void GetTransactionsForDateRange(base::Time from_time,
                                 base::Time to_time,
                                 GetTransactionsCallback callback);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTIONS_H_
