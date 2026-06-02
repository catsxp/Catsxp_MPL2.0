/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TEST_TRANSACTIONS_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TEST_TRANSACTIONS_TEST_UTIL_H_

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace base {
class Time;
}  // namespace base

namespace catsxp_ads {

struct TransactionInfo;

namespace test {

TransactionInfo BuildTransaction(
    double value,
    mojom::AdType mojom_ad_type,
    mojom::ConfirmationType mojom_confirmation_type,
    base::Time reconciled_at,
    bool use_random_uuids);
TransactionInfo BuildUnreconciledTransaction(
    double value,
    mojom::AdType mojom_ad_type,
    mojom::ConfirmationType mojom_confirmation_type,
    bool use_random_uuids);

}  // namespace test

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TEST_TRANSACTIONS_TEST_UTIL_H_
