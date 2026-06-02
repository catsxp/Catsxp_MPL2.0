/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_handler_util.h"

#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/ad_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsAdEventHandlerUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsAdEventHandlerUtilTest, HasFiredAdEvent) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kAdEventFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event);

  // Act & Assert
  EXPECT_TRUE(HasFiredAdEvent(ad, ad_events,
                              mojom::ConfirmationType::kServedImpression));
}

TEST_F(CatsxpAdsAdEventHandlerUtilTest, HasNeverFiredAdEvent) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kAdEventFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event);

  // Act & Assert
  EXPECT_FALSE(HasFiredAdEvent(ad, ad_events,
                               mojom::ConfirmationType::kViewedImpression));
}

TEST_F(CatsxpAdsAdEventHandlerUtilTest, HasFiredAdEventWithinTimeWindow) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kAdEventFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event);

  // Act & Assert
  EXPECT_TRUE(HasFiredAdEventWithinTimeWindow(
      ad, ad_events, mojom::ConfirmationType::kServedImpression,
      /*time_window=*/base::Seconds(5)));
}

TEST_F(CatsxpAdsAdEventHandlerUtilTest, HasNeverFiredAdEventWithinTimeWindow) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kAdEventFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event);

  AdvanceClockBy(base::Seconds(5));

  // Act & Assert
  EXPECT_FALSE(HasFiredAdEventWithinTimeWindow(
      ad, ad_events, mojom::ConfirmationType::kViewedImpression,
      /*time_window=*/base::Seconds(5)));
}

TEST_F(CatsxpAdsAdEventHandlerUtilTest, WasAdServed) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kAdEventFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event);

  // Act & Assert
  EXPECT_TRUE(WasAdServed(ad, ad_events,
                          mojom::NewTabPageAdEventType::kViewedImpression));
}

TEST_F(CatsxpAdsAdEventHandlerUtilTest, WasAdServedIfNoPreviousEvents) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kAdEventFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);

  // Act & Assert
  EXPECT_TRUE(WasAdServed(ad, /*ad_events=*/{},
                          mojom::NewTabPageAdEventType::kServedImpression));
}

TEST_F(CatsxpAdsAdEventHandlerUtilTest, WasAdNeverServed) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kAdEventFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);

  // Act & Assert
  EXPECT_FALSE(WasAdServed(ad, /*ad_events=*/{},
                           mojom::NewTabPageAdEventType::kViewedImpression));
}

TEST_F(CatsxpAdsAdEventHandlerUtilTest,
       ShouldDeduplicateViewedAdEventWithinTimeWindow) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kAdEventFeature, {{"deduplicate_viewed_ad_event_for", "5s"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
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

  AdvanceClockBy(kDeduplicateViewedAdEventFor.Get());

  // Act & Assert
  EXPECT_TRUE(ShouldDeduplicateAdEvent(
      ad, ad_events, mojom::NewTabPageAdEventType::kViewedImpression));
}

TEST_F(CatsxpAdsAdEventHandlerUtilTest,
       ShouldNotDeduplicateViewedAdEventOutOfTimeWindow) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kAdEventFeature, {{"deduplicate_viewed_ad_event_for", "5s"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
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

  AdvanceClockBy(kDeduplicateViewedAdEventFor.Get() + base::Seconds(1));

  // Act & Assert
  EXPECT_FALSE(ShouldDeduplicateAdEvent(
      ad, ad_events, mojom::NewTabPageAdEventType::kViewedImpression));
}

TEST_F(CatsxpAdsAdEventHandlerUtilTest, ShouldAlwaysDeduplicateViewedAdEvent) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kAdEventFeature, {{"deduplicate_viewed_ad_event_for", "0s"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
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

  AdvanceClockTo(test::DistantFuture());

  // Act & Assert
  EXPECT_TRUE(ShouldDeduplicateAdEvent(
      ad, ad_events, mojom::NewTabPageAdEventType::kViewedImpression));
}

TEST_F(CatsxpAdsAdEventHandlerUtilTest,
       ShouldNotDeduplicateViewedAdEventIfAdWasNeverViewed) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kAdEventFeature, {{"deduplicate_viewed_ad_event_for", "5s"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event);

  // Act & Assert
  EXPECT_FALSE(ShouldDeduplicateAdEvent(
      ad, ad_events, mojom::NewTabPageAdEventType::kViewedImpression));
}

TEST_F(CatsxpAdsAdEventHandlerUtilTest,
       ShouldDeduplicateClickedAdEventWithinTimeWindow) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kAdEventFeature, {{"deduplicate_clicked_ad_event_for", "5s"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
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
  const AdEventInfo ad_event_3 = BuildAdEvent(
      ad, mojom::ConfirmationType::kClicked, /*created_at=*/test::Now());
  ad_events.push_back(ad_event_3);

  AdvanceClockBy(kDeduplicateClickedAdEventFor.Get());

  // Act & Assert
  EXPECT_TRUE(ShouldDeduplicateAdEvent(ad, ad_events,
                                       mojom::NewTabPageAdEventType::kClicked));
}

TEST_F(CatsxpAdsAdEventHandlerUtilTest,
       ShouldNotDeduplicateClickedAdEventOutOfTimeWindow) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kAdEventFeature, {{"deduplicate_clicked_ad_event_for", "5s"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
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
  const AdEventInfo ad_event_3 = BuildAdEvent(
      ad, mojom::ConfirmationType::kClicked, /*created_at=*/test::Now());
  ad_events.push_back(ad_event_3);

  AdvanceClockBy(kDeduplicateClickedAdEventFor.Get() + base::Seconds(1));

  // Act & Assert
  EXPECT_FALSE(ShouldDeduplicateAdEvent(
      ad, ad_events, mojom::NewTabPageAdEventType::kClicked));
}

TEST_F(CatsxpAdsAdEventHandlerUtilTest, ShouldAlwaysDeduplicateClickedAdEvent) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kAdEventFeature, {{"deduplicate_clicked_ad_event_for", "0s"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
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
  const AdEventInfo ad_event_3 = BuildAdEvent(
      ad, mojom::ConfirmationType::kClicked, /*created_at=*/test::Now());
  ad_events.push_back(ad_event_3);

  AdvanceClockTo(test::DistantFuture());

  // Act & Assert
  EXPECT_TRUE(ShouldDeduplicateAdEvent(ad, ad_events,
                                       mojom::NewTabPageAdEventType::kClicked));
}

TEST_F(CatsxpAdsAdEventHandlerUtilTest,
       ShouldNotDeduplicateClickedAdEventIfAdWasNeverClicked) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kAdEventFeature, {{"deduplicate_clicked_ad_event_for", "5s"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
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
  EXPECT_FALSE(ShouldDeduplicateAdEvent(
      ad, ad_events, mojom::NewTabPageAdEventType::kClicked));
}

}  // namespace catsxp_ads
