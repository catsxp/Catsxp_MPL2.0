/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/statement/ads_received_util.h"

#include <algorithm>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

size_t GetAdsReceivedForDateRange(const TransactionList& transactions,
                                  base::Time from_time,
                                  base::Time to_time) {
  const bool should_include_zero_value_transactions =
      UserHasJoinedCatsxpRewardsAndNotConnectedWallet();

  return std::ranges::count_if(
      transactions,
      [from_time, to_time, should_include_zero_value_transactions](
          const TransactionInfo& transaction) {
        return transaction.confirmation_type ==
                   mojom::ConfirmationType::kViewedImpression &&
               transaction.created_at >= from_time &&
               transaction.created_at <= to_time &&
               (should_include_zero_value_transactions ||
                transaction.value > 0);
      });
}

}  // namespace catsxp_ads
