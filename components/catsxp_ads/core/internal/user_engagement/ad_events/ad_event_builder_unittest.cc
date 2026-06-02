/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"

#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/ad_info.h"
#include "url/gurl.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsAdEventBuilderTest : public test::TestBase {};

TEST_F(CatsxpAdsAdEventBuilderTest, BuildAdEvent) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/false);

  // Act
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Assert
  EXPECT_THAT(
      ad_event,
      ::testing::FieldsAre(
          mojom::AdType::kNotificationAd,
          mojom::ConfirmationType::kViewedImpression, test::kPlacementId,
          test::kCreativeInstanceId, test::kCreativeSetId, test::kCampaignId,
          test::kAdvertiserId, test::kSegment, GURL(test::kTargetUrl),
          /*created_at*/ test::Now()));
}

TEST_F(CatsxpAdsAdEventBuilderTest, RebuildAdEvent) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/false);

  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act
  const AdEventInfo rebuilt_ad_event =
      RebuildAdEvent(ad_event, mojom::ConfirmationType::kConversion,
                     /*created_at=*/test::DistantFuture());

  // Assert
  EXPECT_THAT(
      rebuilt_ad_event,
      ::testing::FieldsAre(
          mojom::AdType::kNotificationAd, mojom::ConfirmationType::kConversion,
          test::kPlacementId, test::kCreativeInstanceId, test::kCreativeSetId,
          test::kCampaignId, test::kAdvertiserId, test::kSegment,
          GURL(test::kTargetUrl), /*created_at*/ test::DistantFuture()));
}

}  // namespace catsxp_ads
