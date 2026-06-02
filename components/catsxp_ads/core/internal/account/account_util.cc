/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/account_util.h"

#include <utility>

#include "base/notreached.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_core/ads_core_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

bool IsAllowedToDeposit(const std::string& creative_instance_id,
                        mojom::AdType mojom_ad_type,
                        mojom::ConfirmationType mojom_confirmation_type) {
  if (mojom_ad_type == mojom::AdType::kNewTabPageAd &&
      !ShouldReportMetric(creative_instance_id)) {
    // Do not allow deposits for new tab page ads if we should not report
    // metrics for the given creative instance.
    return false;
  }

  if (UserHasJoinedCatsxpRewards()) {
    // Always allow deposits for Rewards users.
    return true;
  }

  // Evaluate deposit eligibility for non-Rewards users based on ad type and
  // other conditions.
  switch (mojom_ad_type) {
    case mojom::AdType::kNewTabPageAd: {
      // Only allow deposits for non-Rewards users who have opted into new tab
      // page ads.
      return UserHasOptedInToNewTabPageAds();
    }

    case mojom::AdType::kNotificationAd: {
      // Never allow deposits because users cannot opt into notification ads
      // without joining Catsxp Rewards.
      return false;
    }

    case mojom::AdType::kSearchResultAd: {
      // Only allow conversion deposits for non-Rewards users.
      return mojom_confirmation_type == mojom::ConfirmationType::kConversion;
    }

    case mojom::AdType::kUndefined: {
      break;
    }
  }

  NOTREACHED() << "Unexpected value for mojom::AdType: "
               << std::to_underlying(mojom_ad_type);
}

}  // namespace catsxp_ads
