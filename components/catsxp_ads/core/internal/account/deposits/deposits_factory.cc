/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/deposits/deposits_factory.h"

#include <utility>

#include "base/notreached.h"
#include "catsxp/components/catsxp_ads/core/internal/account/deposits/cash_deposit.h"
#include "catsxp/components/catsxp_ads/core/internal/account/deposits/non_cash_deposit.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

std::unique_ptr<DepositInterface> DepositsFactory::Build(
    mojom::ConfirmationType mojom_confirmation_type) {
  if (!UserHasJoinedCatsxpRewardsAndConnectedWallet()) {
    // If the user has not joined Catsxp Rewards and connected a wallet, deposits
    // are treated as non-rewardable.
    return std::make_unique<NonCashDeposit>();
  }

  switch (mojom_confirmation_type) {
    case mojom::ConfirmationType::kViewedImpression: {
      // Rewardable.
      return std::make_unique<CashDeposit>();
    }

    case mojom::ConfirmationType::kClicked:
    case mojom::ConfirmationType::kDismissed:
    case mojom::ConfirmationType::kServedImpression:
    case mojom::ConfirmationType::kLanded:
    case mojom::ConfirmationType::kSavedAd:
    case mojom::ConfirmationType::kMarkAdAsInappropriate:
    case mojom::ConfirmationType::kLikedAd:
    case mojom::ConfirmationType::kDislikedAd:
    case mojom::ConfirmationType::kConversion:
    case mojom::ConfirmationType::kInteraction:
    case mojom::ConfirmationType::kMediaPlay:
    case mojom::ConfirmationType::kMedia25:
    case mojom::ConfirmationType::kMedia100: {
      // Non-rewardable.
      return std::make_unique<NonCashDeposit>();
    }

    case mojom::ConfirmationType::kUndefined: {
      break;
    }
  }

  NOTREACHED() << "Unexpected value for mojom::ConfirmationType: "
               << std::to_underlying(mojom_confirmation_type);
}

}  // namespace catsxp_ads
