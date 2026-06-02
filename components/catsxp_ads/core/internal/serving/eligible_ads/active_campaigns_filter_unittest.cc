/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/active_campaigns_filter.h"

#include "base/test/task_environment.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/test/creative_notification_ad_test_util.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsActiveCampaignsFilterTest : public ::testing::Test {
 protected:
  base::test::TaskEnvironment task_environment_{
      base::test::TaskEnvironment::TimeSource::MOCK_TIME};
};

TEST_F(CatsxpAdsActiveCampaignsFilterTest, RemoveCreativeAdForExpiredCampaign) {
  // Arrange
  CreativeNotificationAdList creative_ads;
  CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*should_generate_random_uuids=*/true);
  creative_ad.end_at = test::Now() - base::Days(1);
  creative_ads.push_back(creative_ad);

  // Act
  FilterInactiveCampaignCreativeAds(creative_ads);

  // Assert
  EXPECT_THAT(creative_ads, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsActiveCampaignsFilterTest, RemoveCreativeAdForFutureCampaign) {
  // Arrange
  CreativeNotificationAdList creative_ads;
  CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*should_generate_random_uuids=*/true);
  creative_ad.start_at = test::Now() + base::Days(1);
  creative_ad.end_at = test::Now() + base::Days(30);
  creative_ads.push_back(creative_ad);

  // Act
  FilterInactiveCampaignCreativeAds(creative_ads);

  // Assert
  EXPECT_THAT(creative_ads, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsActiveCampaignsFilterTest,
       KeepCreativeAdWhenNowIsExactlyAtCampaignStart) {
  // Arrange
  CreativeNotificationAdList creative_ads;
  CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*should_generate_random_uuids=*/true);
  creative_ad.start_at = test::Now();
  creative_ad.end_at = test::Now() + base::Days(30);
  creative_ads.push_back(creative_ad);

  // Act
  FilterInactiveCampaignCreativeAds(creative_ads);

  // Assert
  EXPECT_THAT(creative_ads, ::testing::ElementsAre(creative_ad));
}

TEST_F(CatsxpAdsActiveCampaignsFilterTest,
       KeepCreativeAdWhenNowIsExactlyAtCampaignEnd) {
  // Arrange
  CreativeNotificationAdList creative_ads;
  CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*should_generate_random_uuids=*/true);
  creative_ad.start_at = test::Now() - base::Days(30);
  creative_ad.end_at = test::Now();
  creative_ads.push_back(creative_ad);

  // Act
  FilterInactiveCampaignCreativeAds(creative_ads);

  // Assert
  EXPECT_THAT(creative_ads, ::testing::ElementsAre(creative_ad));
}

TEST_F(CatsxpAdsActiveCampaignsFilterTest, OnlyKeepCreativeAdForActiveCampaign) {
  // Arrange
  CreativeNotificationAdList creative_ads;

  CreativeNotificationAdInfo active_creative_ad =
      test::BuildCreativeNotificationAd(/*should_generate_random_uuids=*/true);
  active_creative_ad.start_at = test::Now() - base::Days(1);
  active_creative_ad.end_at = test::Now() + base::Days(1);
  creative_ads.push_back(active_creative_ad);

  CreativeNotificationAdInfo expired_creative_ad =
      test::BuildCreativeNotificationAd(/*should_generate_random_uuids=*/true);
  expired_creative_ad.end_at = test::Now() - base::Days(1);
  creative_ads.push_back(expired_creative_ad);

  // Act
  FilterInactiveCampaignCreativeAds(creative_ads);

  // Assert
  EXPECT_THAT(creative_ads, ::testing::ElementsAre(active_creative_ad));
}

}  // namespace catsxp_ads
