/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/redeem_confirmation_factory.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/non_reward/redeem_non_reward_confirmation.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/reward/redeem_reward_confirmation.h"

namespace catsxp_ads {

// static
void RedeemConfirmationFactory::BuildAndRedeemConfirmation(
    base::WeakPtr<RedeemConfirmationDelegate> delegate,
    const ConfirmationInfo& confirmation) {
  if (!confirmation.reward) {
    return RedeemNonRewardConfirmation::CreateAndRedeem(std::move(delegate),
                                                        confirmation);
  }

  RedeemRewardConfirmation::CreateAndRedeem(std::move(delegate), confirmation);
}

}  // namespace catsxp_ads
