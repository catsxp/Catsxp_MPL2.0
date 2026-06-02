/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsUserIdleDetectionTest : public test::TestBase {};

TEST_F(CatsxpAdsUserIdleDetectionTest, RewardsUserDidBecomeActive) {
  // Act & Assert
  EXPECT_CALL(ads_client_mock_, Log).Times(::testing::AnyNumber());
  EXPECT_CALL(ads_client_mock_,
              Log(/*file=*/::testing::_, /*line=*/::testing::_,
                  /*verbose_level=*/::testing::_, "User is active after 10 s"));
  ads_client_notifier_.NotifyUserDidBecomeActive(
      /*idle_time=*/base::Seconds(10),
      /*screen_was_locked=*/false);
}

TEST_F(CatsxpAdsUserIdleDetectionTest, NonRewardsUserDidBecomeActive) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  EXPECT_CALL(ads_client_mock_, Log).Times(0);
  ads_client_notifier_.NotifyUserDidBecomeActive(
      /*idle_time=*/base::Seconds(10),
      /*screen_was_locked=*/false);
}

TEST_F(CatsxpAdsUserIdleDetectionTest,
       RewardsUserDidBecomeActiveWhileScreenWasLocked) {
  // Act & Assert
  EXPECT_CALL(ads_client_mock_, Log).Times(::testing::AnyNumber());
  EXPECT_CALL(ads_client_mock_,
              Log(/*file=*/::testing::_, /*line=*/::testing::_,
                  /*verbose_level=*/::testing::_, "User is active after 10 s"));
  EXPECT_CALL(ads_client_mock_,
              Log(/*file=*/::testing::_, /*line=*/::testing::_,
                  /*verbose_level=*/::testing::_,
                  "Screen was locked before the user become active"));
  ads_client_notifier_.NotifyUserDidBecomeActive(
      /*idle_time=*/base::Seconds(10),
      /*screen_was_locked=*/true);
}

TEST_F(CatsxpAdsUserIdleDetectionTest,
       NonRewardsUserDidBecomeActiveWhileScreenWasLocked) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  EXPECT_CALL(ads_client_mock_, Log).Times(0);
  ads_client_notifier_.NotifyUserDidBecomeActive(
      /*idle_time=*/base::Seconds(10),
      /*screen_was_locked=*/true);
}

TEST_F(CatsxpAdsUserIdleDetectionTest, RewardsUserDidBecomeIdle) {
  // Act & Assert
  EXPECT_CALL(ads_client_mock_, Log);
  ads_client_notifier_.NotifyUserDidBecomeIdle();
}

TEST_F(CatsxpAdsUserIdleDetectionTest, NonRewardsUserDidBecomeIdle) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  EXPECT_CALL(ads_client_mock_, Log).Times(0);
  ads_client_notifier_.NotifyUserDidBecomeIdle();
}

}  // namespace catsxp_ads
