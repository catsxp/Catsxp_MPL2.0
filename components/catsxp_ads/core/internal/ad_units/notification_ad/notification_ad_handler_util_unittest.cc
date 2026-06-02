/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ad_units/notification_ad/notification_ad_handler_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsNotificationAdUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsNotificationAdUtilTest, CanServeIfUserIsActive) {
  // Act & Assert
  EXPECT_TRUE(CanServeIfUserIsActive());
}

TEST_F(CatsxpAdsNotificationAdUtilTest, CannotServeIfUserIsActive) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kAndroid);
  OperatingSystem::SetForTesting(&fake_operating_system_);

  // Act & Assert
  EXPECT_FALSE(CanServeIfUserIsActive());
}

TEST_F(CatsxpAdsNotificationAdUtilTest, ShouldServe) {
  // Act & Assert
  EXPECT_TRUE(ShouldServe());
}

TEST_F(CatsxpAdsNotificationAdUtilTest,
       ShouldNotServeIfOptedOutOfNotificationAds) {
  // Arrange
  test::OptOutOfNotificationAds();

  // Act & Assert
  EXPECT_FALSE(ShouldServe());
}

TEST_F(CatsxpAdsNotificationAdUtilTest, CanServeAtRegularIntervals) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kAndroid);
  OperatingSystem::SetForTesting(&fake_operating_system_);

  // Act & Assert
  EXPECT_TRUE(CanServeAtRegularIntervals());
}

TEST_F(CatsxpAdsNotificationAdUtilTest, CannotServeAtRegularIntervals) {
  // Act & Assert
  EXPECT_FALSE(CanServeAtRegularIntervals());
}

}  // namespace catsxp_ads
