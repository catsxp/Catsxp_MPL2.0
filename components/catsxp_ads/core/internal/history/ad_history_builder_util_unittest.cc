/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/history/ad_history_builder_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/notification_ad_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/test/creative_notification_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/notification_ad/notification_ad_info.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsAdHistoryBuilderUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsAdHistoryBuilderUtilTest, BuildAdHistoryItem) {
  // Arrange
  const CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  const NotificationAdInfo ad = BuildNotificationAd(creative_ad);

  // Act
  const AdHistoryItemInfo ad_history_item = BuildAdHistoryItem(
      ad, mojom::ConfirmationType::kViewedImpression, ad.title, ad.body);

  // Assert
  EXPECT_THAT(ad_history_item,
              ::testing::FieldsAre(
                  /*created_at*/ test::Now(), ad.type,
                  mojom::ConfirmationType::kViewedImpression, ad.placement_id,
                  ad.creative_instance_id, ad.creative_set_id, ad.campaign_id,
                  ad.advertiser_id, ad.segment, ad.title,
                  /*description*/ ad.body, ad.target_url));
}

}  // namespace catsxp_ads
