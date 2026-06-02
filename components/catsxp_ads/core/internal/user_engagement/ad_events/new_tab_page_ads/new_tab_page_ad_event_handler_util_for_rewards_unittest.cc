/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ad_units/new_tab_page_ad/test/new_tab_page_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/new_tab_page_ads/new_tab_page_ad_event_handler_util.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsNewTabPageAdEventHandlerUtilForRewardsTest
    : public test::TestBase {};

TEST_F(CatsxpAdsNewTabPageAdEventHandlerUtilForRewardsTest,
       IsAllowedToFireAdEvent) {
  // Act & Assert
  EXPECT_TRUE(IsAllowedToFireAdEvent());
}

TEST_F(CatsxpAdsNewTabPageAdEventHandlerUtilForRewardsTest,
       IsNotAllowedToFireAdEvent) {
  // Arrange
  test::OptOutOfNewTabPageAds();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToFireAdEvent());
}

TEST_F(CatsxpAdsNewTabPageAdEventHandlerUtilForRewardsTest,
       ShouldFireNonDuplicateViewedEvent) {
  // Arrange
  const NewTabPageAdInfo ad =
      test::BuildNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                              /*use_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event);

  // Act & Assert
  EXPECT_TRUE(ShouldFireAdEvent(
      ad, ad_events, mojom::NewTabPageAdEventType::kViewedImpression));
}

TEST_F(CatsxpAdsNewTabPageAdEventHandlerUtilForRewardsTest,
       ShouldNotFireDuplicateViewedEvent) {
  // Arrange
  const NewTabPageAdInfo ad =
      test::BuildNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                              /*use_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event_1 =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_1);
  const AdEventInfo ad_event_2 =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_2);

  // Act & Assert
  EXPECT_FALSE(ShouldFireAdEvent(
      ad, ad_events, mojom::NewTabPageAdEventType::kViewedImpression));
}

TEST_F(CatsxpAdsNewTabPageAdEventHandlerUtilForRewardsTest,
       ShouldFireNonDuplicateClickedEvent) {
  // Arrange
  const NewTabPageAdInfo ad =
      test::BuildNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                              /*use_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event);

  // Act & Assert
  EXPECT_TRUE(
      ShouldFireAdEvent(ad, ad_events, mojom::NewTabPageAdEventType::kClicked));
}

TEST_F(CatsxpAdsNewTabPageAdEventHandlerUtilForRewardsTest,
       ShouldNotFireDuplicateClickedEvent) {
  // Arrange
  const NewTabPageAdInfo ad =
      test::BuildNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                              /*use_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event_1 =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_1);
  const AdEventInfo ad_event_2 = BuildAdEvent(
      ad, mojom::ConfirmationType::kClicked, /*created_at=*/test::Now());
  ad_events.push_back(ad_event_2);

  // Act & Assert
  EXPECT_FALSE(
      ShouldFireAdEvent(ad, ad_events, mojom::NewTabPageAdEventType::kClicked));
}

}  // namespace catsxp_ads
