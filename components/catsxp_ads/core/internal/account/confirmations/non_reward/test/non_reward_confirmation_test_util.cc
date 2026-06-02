/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/non_reward/test/non_reward_confirmation_test_util.h"

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/non_reward/non_reward_confirmation_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/reward/reward_confirmation_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transactions_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads::test {

std::optional<ConfirmationInfo> BuildNonRewardConfirmation(
    bool use_random_uuids) {
  CHECK(!UserHasJoinedCatsxpRewards());

  const TransactionInfo transaction = BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression, use_random_uuids);
  return BuildNonRewardConfirmation(transaction, /*user_data=*/{});
}

}  // namespace catsxp_ads::test
