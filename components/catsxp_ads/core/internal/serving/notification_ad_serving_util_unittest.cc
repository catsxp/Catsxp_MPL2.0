/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/notification_ad_serving_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system_types.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsNotificationAdServingUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsNotificationAdServingUtilTest,
       ShouldServeAdsAtRegularIntervalsOnIOS) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kIOS);

  // Act & Assert
  EXPECT_TRUE(ShouldServeAdsAtRegularIntervals());
}

TEST_F(CatsxpAdsNotificationAdServingUtilTest,
       ShouldServeAdsAtRegularIntervalsOnAndroid) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kAndroid);

  // Act & Assert
  EXPECT_TRUE(ShouldServeAdsAtRegularIntervals());
}

TEST_F(CatsxpAdsNotificationAdServingUtilTest,
       ShouldNotServeAdsAtRegularIntervalsOnMacOS) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kMacOS);

  // Act & Assert
  EXPECT_FALSE(ShouldServeAdsAtRegularIntervals());
}

TEST_F(CatsxpAdsNotificationAdServingUtilTest,
       ShouldNotServeAdsAtRegularIntervalsOnWindows) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kWindows);

  // Act & Assert
  EXPECT_FALSE(ShouldServeAdsAtRegularIntervals());
}

TEST_F(CatsxpAdsNotificationAdServingUtilTest,
       ShouldNotServeAdsAtRegularIntervalsOnLinux) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kLinux);

  // Act & Assert
  EXPECT_FALSE(ShouldServeAdsAtRegularIntervals());
}

TEST_F(CatsxpAdsNotificationAdServingUtilTest, SetServeAdAt) {
  // Act
  SetServeAdAt(test::DistantFuture());

  // Assert
  EXPECT_EQ(test::DistantFuture(), ServeAdAt());
}

TEST_F(CatsxpAdsNotificationAdServingUtilTest,
       CalculateDelayBeforeServingTheFirstAd) {
  // Act & Assert
  EXPECT_EQ(base::Minutes(2), CalculateDelayBeforeServingAnAd());
}

TEST_F(CatsxpAdsNotificationAdServingUtilTest,
       CalculateDelayBeforeServingAPastDueAd) {
  // Arrange
  SetServeAdAt(test::DistantPast());

  // Act & Assert
  EXPECT_EQ(base::Minutes(1), CalculateDelayBeforeServingAnAd());
}

TEST_F(CatsxpAdsNotificationAdServingUtilTest, CalculateDelayBeforeServingAnAd) {
  // Arrange
  SetServeAdAt(test::DistantFuture());

  // Act & Assert
  EXPECT_EQ(test::DistantFuture() - test::Now(),
            CalculateDelayBeforeServingAnAd());
}

TEST_F(CatsxpAdsNotificationAdServingUtilTest,
       CalculateMinimumDelayBeforeServingAnAd) {
  // Arrange
  SetServeAdAt(test::Now());

  AdvanceClockBy(base::Milliseconds(1));

  // Act & Assert
  EXPECT_EQ(base::Minutes(1), CalculateDelayBeforeServingAnAd());
}

}  // namespace catsxp_ads
