/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transactions_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transaction_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads::test {

TransactionInfo BuildTransaction(
    double value,
    mojom::AdType mojom_ad_type,
    mojom::ConfirmationType mojom_confirmation_type,
    base::Time reconciled_at,
    bool use_random_uuids) {
  TransactionInfo transaction;

  transaction.id = RandomUuidOr(use_random_uuids, kTransactionId);
  transaction.created_at = Now();
  transaction.creative_instance_id =
      RandomUuidOr(use_random_uuids, kCreativeInstanceId);
  transaction.segment = kSegment;
  transaction.value = value;
  transaction.ad_type = mojom_ad_type;
  transaction.confirmation_type = mojom_confirmation_type;
  if (!reconciled_at.is_null()) {
    transaction.reconciled_at = reconciled_at;
  }

  return transaction;
}

TransactionInfo BuildUnreconciledTransaction(
    double value,
    mojom::AdType mojom_ad_type,
    mojom::ConfirmationType mojom_confirmation_type,
    bool use_random_uuids) {
  return BuildTransaction(value, mojom_ad_type, mojom_confirmation_type,
                          /*reconciled_at=*/{}, use_random_uuids);
}

}  // namespace catsxp_ads::test
