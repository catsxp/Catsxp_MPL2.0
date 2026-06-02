/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/pacing/pacing.h"

#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/test/creative_notification_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/pacing/pacing_random_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

std::vector<double> GetPacingRandomNumbers() {
  return {0.0, 0.5, 0.99};
}

}  // namespace

class CatsxpAdsPacingTest : public test::TestBase {};
TEST_F(CatsxpAdsPacingTest, PaceCreativeAdsWithMinPassThroughRate) {
  // Arrange
  CreativeNotificationAdList creative_ads;
  CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  creative_ad.pass_through_rate = 0.0;
  creative_ads.push_back(creative_ad);

  // Act & Assert
  for (const double random_number : GetPacingRandomNumbers()) {
    const ScopedPacingRandomNumberSetterForTesting scoped_setter(random_number);
    PaceCreativeAds(creative_ads);
    EXPECT_THAT(creative_ads, ::testing::IsEmpty());
  }
}

TEST_F(CatsxpAdsPacingTest, DoNotPaceCreativeAdsWithMaxPassThroughRate) {
  // Arrange
  CreativeNotificationAdList creative_ads;
  CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  creative_ad.pass_through_rate = 1.0;
  creative_ads.push_back(creative_ad);

  // Act & Assert
  const CreativeNotificationAdList expected_creative_ads = {creative_ad};
  for (const double random_number : GetPacingRandomNumbers()) {
    const ScopedPacingRandomNumberSetterForTesting scoped_setter(random_number);
    PaceCreativeAds(creative_ads);
    EXPECT_EQ(expected_creative_ads, creative_ads);
  }
}

TEST_F(CatsxpAdsPacingTest,
       PaceCreativeAdIfPacingIsGreaterThanOrEqualToPassThroughRate) {
  // Arrange
  CreativeNotificationAdList creative_ads;
  CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  creative_ad.pass_through_rate = 0.5;
  creative_ads.push_back(creative_ad);

  const ScopedPacingRandomNumberSetterForTesting scoped_setter(0.7);

  // Act
  PaceCreativeAds(creative_ads);

  // Assert
  EXPECT_THAT(creative_ads, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsPacingTest,
       DoNotPaceCreativeAdWhenPacingIsLessThanPassThroughRate) {
  // Arrange
  CreativeNotificationAdList creative_ads;

  CreativeNotificationAdInfo creative_ad_1 =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  creative_ad_1.pass_through_rate = 0.1;
  creative_ads.push_back(creative_ad_1);

  CreativeNotificationAdInfo creative_ad_2 =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  creative_ad_2.pass_through_rate = 0.5;
  creative_ads.push_back(creative_ad_2);

  const ScopedPacingRandomNumberSetterForTesting scoped_setter(0.3);

  // Act
  PaceCreativeAds(creative_ads);

  // Assert
  const CreativeNotificationAdList expected_creative_ads = {creative_ad_2};
  EXPECT_EQ(expected_creative_ads, creative_ads);
}

}  // namespace catsxp_ads
