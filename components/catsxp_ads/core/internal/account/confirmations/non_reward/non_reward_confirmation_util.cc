/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/non_reward/non_reward_confirmation_util.h"

#include <utility>

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/user_data_builder/confirmation_user_data_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/user_data/user_data_info.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"

namespace catsxp_ads {

std::optional<ConfirmationInfo> BuildNonRewardConfirmation(
    const TransactionInfo& transaction,
    base::DictValue user_data) {
  CHECK(transaction.IsValid());
  CHECK(!UserHasJoinedCatsxpRewardsAndConnectedWallet());

  ConfirmationInfo confirmation;
  confirmation.transaction_id = transaction.id;
  confirmation.creative_instance_id = transaction.creative_instance_id;
  confirmation.type = transaction.confirmation_type;
  confirmation.ad_type = transaction.ad_type;
  confirmation.created_at = transaction.created_at;
  confirmation.user_data =
      BuildConfirmationUserData(transaction, std::move(user_data));

  return confirmation;
}

}  // namespace catsxp_ads
