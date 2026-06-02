/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversions_util_internal.h"

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/ad_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConversionsUtilInternalTest : public test::TestBase {};

TEST_F(CatsxpAdsConversionsUtilInternalTest,
       CanOnlyConvertClickThroughAdEventForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  for (size_t i = 0; i < static_cast<size_t>(mojom::AdType::kMaxValue); ++i) {
    const auto mojom_ad_type = static_cast<mojom::AdType>(i);

    const AdInfo ad = test::BuildAd(mojom_ad_type,
                                    /*use_random_uuids=*/false);

    for (size_t j = 0;
         j < static_cast<size_t>(mojom::ConfirmationType::kMaxValue); ++j) {
      const auto confirmation_type = static_cast<mojom::ConfirmationType>(j);

      const bool expected_can_convert_ad_event =
          confirmation_type == mojom::ConfirmationType::kClicked;

      const AdEventInfo ad_event =
          BuildAdEvent(ad, confirmation_type, /*created_at=*/test::Now());
      EXPECT_EQ(expected_can_convert_ad_event, CanConvertAdEvent(ad_event));
    }
  }
}

TEST_F(CatsxpAdsConversionsUtilInternalTest,
       CanConvertViewOrClickThroughAdEventForRewardsUser) {
  // Act & Assert
  for (size_t i = 0; i < static_cast<size_t>(mojom::AdType::kMaxValue); ++i) {
    const auto mojom_ad_type = static_cast<mojom::AdType>(i);

    const AdInfo ad = test::BuildAd(mojom_ad_type,
                                    /*use_random_uuids=*/false);

    for (size_t j = 0;
         j < static_cast<size_t>(mojom::ConfirmationType::kMaxValue); ++j) {
      const auto confirmation_type = static_cast<mojom::ConfirmationType>(j);

      // Only viewed and clicked ad events are allowed to be converted.
      const bool expected_can_convert_ad_event =
          confirmation_type == mojom::ConfirmationType::kViewedImpression ||
          confirmation_type == mojom::ConfirmationType::kClicked;

      const AdEventInfo ad_event =
          BuildAdEvent(ad, confirmation_type, /*created_at=*/test::Now());
      EXPECT_EQ(expected_can_convert_ad_event, CanConvertAdEvent(ad_event));
    }
  }
}

}  // namespace catsxp_ads
