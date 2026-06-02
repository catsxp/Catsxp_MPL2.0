/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/statement/ads_summary_util.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

base::flat_map<mojom::AdType, int32_t> GetAdsSummaryForDateRange(
    const TransactionList& transactions,
    base::Time from_time,
    base::Time to_time) {
  base::flat_map<mojom::AdType, int32_t> ads_summary;

  const bool should_include_zero_value_transactions =
      UserHasJoinedCatsxpRewardsAndNotConnectedWallet();

  for (const auto& transaction : transactions) {
    if (transaction.confirmation_type ==
            mojom::ConfirmationType::kViewedImpression &&
        transaction.created_at >= from_time &&
        transaction.created_at <= to_time &&
        (should_include_zero_value_transactions || transaction.value > 0)) {
      ++ads_summary[transaction.ad_type];
    }
  }

  return ads_summary;
}

}  // namespace catsxp_ads
