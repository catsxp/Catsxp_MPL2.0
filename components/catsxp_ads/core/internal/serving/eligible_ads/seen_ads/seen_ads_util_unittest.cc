/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/seen_ads/seen_ads_util.h"

#include "catsxp/components/catsxp_ads/core/internal/ad_units/notification_ad/test/notification_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/notification_ad/notification_ad_info.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsSeenAdsUtilTest, DoNotGetLastSeenAdAtForEmptyAdEvents) {
  // Arrange
  const NotificationAdInfo ad =
      test::BuildNotificationAd(/*use_random_uuids=*/true);

  // Act & Assert
  EXPECT_FALSE(GetLastSeenAdAt(/*ad_events=*/{}, ad.creative_instance_id));
}

TEST(CatsxpAdsSeenAdsUtilTest, DoNotGetLastSeenAdAtForUnseenAd) {
  // Arrange
  const NotificationAdInfo ad_1 =
      test::BuildNotificationAd(/*use_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      BuildAdEvent(ad_1, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now() - base::Hours(12));
  ad_events.push_back(ad_event);

  const NotificationAdInfo ad_2 =
      test::BuildNotificationAd(/*use_random_uuids=*/true);

  // Act & Assert
  EXPECT_FALSE(GetLastSeenAdAt(ad_events, ad_2.creative_instance_id));
}

TEST(CatsxpAdsSeenAdsUtilTest, GetLastSeenAdAt) {
  // Arrange
  const NotificationAdInfo ad_1 =
      test::BuildNotificationAd(/*use_random_uuids=*/true);

  const NotificationAdInfo ad_2 =
      test::BuildNotificationAd(/*use_random_uuids=*/true);

  const base::Time now = test::Now();

  AdEventList ad_events;

  const AdEventInfo ad_event_4 =
      BuildAdEvent(ad_1, mojom::ConfirmationType::kConversion,
                   /*created_at=*/now - base::Hours(3));
  ad_events.push_back(ad_event_4);

  const AdEventInfo ad_event_3 =
      BuildAdEvent(ad_1, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/now - base::Hours(6));
  ad_events.push_back(ad_event_3);

  const AdEventInfo ad_event_2 =
      BuildAdEvent(ad_2, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/now - base::Hours(11));
  ad_events.push_back(ad_event_2);

  const AdEventInfo ad_event_1 =
      BuildAdEvent(ad_1, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/now - base::Hours(12));
  ad_events.push_back(ad_event_1);

  // Act & Assert
  EXPECT_EQ(now - base::Hours(6),
            GetLastSeenAdAt(ad_events, ad_1.creative_instance_id));
}

}  // namespace catsxp_ads
