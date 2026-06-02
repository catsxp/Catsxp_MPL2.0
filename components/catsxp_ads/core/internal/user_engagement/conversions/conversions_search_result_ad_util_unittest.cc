/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversions_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/ad_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConversionsSearchResultAdUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsConversionsSearchResultAdUtilTest,
       AllowedToConvertViewedAdEvent) {
  // Arrange
  const AdInfo ad =
      test::BuildAd(mojom::AdType::kSearchResultAd, /*use_random_uuids=*/
                    true);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_TRUE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(CatsxpAdsConversionsSearchResultAdUtilTest,
       NotAllowedToConvertViewedAdEventIfOptedOutOfSearchResultAds) {
  // Arrange
  test::OptOutOfSearchResultAds();

  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*use_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_FALSE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(CatsxpAdsConversionsSearchResultAdUtilTest,
       AllowedToConvertClickedAdEvent) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*use_random_uuids=*/false);
  const AdEventInfo ad_event = BuildAdEvent(
      ad, mojom::ConfirmationType::kClicked, /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_TRUE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(CatsxpAdsConversionsSearchResultAdUtilTest,
       NotAllowedToConvertClickedAdEventIfOptedOutOfSearchResultAds) {
  // Arrange
  test::OptOutOfSearchResultAds();

  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*use_random_uuids=*/false);
  const AdEventInfo ad_event = BuildAdEvent(
      ad, mojom::ConfirmationType::kClicked, /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_FALSE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(CatsxpAdsConversionsSearchResultAdUtilTest,
       NotAllowedToConvertNonViewedOrClickedAdEvents) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*use_random_uuids=*/false);

  // Act & Assert
  for (size_t i = 0;
       i < static_cast<size_t>(mojom::ConfirmationType::kMaxValue); ++i) {
    const auto confirmation_type = static_cast<mojom::ConfirmationType>(i);
    if (confirmation_type == mojom::ConfirmationType::kViewedImpression ||
        confirmation_type == mojom::ConfirmationType::kClicked) {
      continue;
    }

    const AdEventInfo ad_event =
        BuildAdEvent(ad, confirmation_type, /*created_at=*/test::Now());
    EXPECT_FALSE(IsAllowedToConvertAdEvent(ad_event));
  }
}

TEST_F(CatsxpAdsConversionsSearchResultAdUtilTest,
       NotAllowedToConvertViewedAdEventForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*use_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_FALSE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(CatsxpAdsConversionsSearchResultAdUtilTest,
       AllowedToConvertClickedAdEventForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*use_random_uuids=*/false);
  const AdEventInfo ad_event = BuildAdEvent(
      ad, mojom::ConfirmationType::kClicked, /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_TRUE(IsAllowedToConvertAdEvent(ad_event));
}

}  // namespace catsxp_ads
