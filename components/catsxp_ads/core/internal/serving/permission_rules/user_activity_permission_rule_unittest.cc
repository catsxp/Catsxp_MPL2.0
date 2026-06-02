/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/user_activity_permission_rule.h"

#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_manager.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsUserActivityPermissionRuleTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    scoped_feature_list_.InitAndEnableFeatureWithParameters(
        kUserActivityFeature, {{"triggers", "0D=1.0;0E=1.0;08=1.0"},
                               {"time_window", "1h"},
                               {"threshold", "2.0"}});
  }

  base::test::ScopedFeatureList scoped_feature_list_;
};

TEST_F(CatsxpAdsUserActivityPermissionRuleTest,
       ShouldAllowIfUserActivityScoreIsEqualToTheThreshold) {
  // Arrange
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClosedTab);

  // Act & Assert
  EXPECT_TRUE(HasUserActivityPermission());
}

TEST_F(CatsxpAdsUserActivityPermissionRuleTest,
       ShouldAllowIfUserHasNotJoinedCatsxpRewards) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  EXPECT_TRUE(HasUserActivityPermission());
}

TEST_F(
    CatsxpAdsUserActivityPermissionRuleTest,
    ShouldAllowIfUserHasJoinedCatsxpRewardsAndNotConnectedWalletAndUserActivityScoreIsLessThanThreshold) {
  // Arrange
  test::DisconnectExternalCatsxpRewardsWallet();

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);

  // Act & Assert
  EXPECT_TRUE(HasUserActivityPermission());
}

TEST_F(CatsxpAdsUserActivityPermissionRuleTest,
       ShouldAllowIfUserActivityScoreIsGreaterThanThreshold) {
  // Arrange
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStartedPlayingMedia);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClosedTab);

  // Act & Assert
  EXPECT_TRUE(HasUserActivityPermission());
}

TEST_F(CatsxpAdsUserActivityPermissionRuleTest,
       ShouldNotAllowIfUserActivityScoreIsLessThanThreshold) {
  // Arrange
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);

  // Act & Assert
  EXPECT_FALSE(HasUserActivityPermission());
}

}  // namespace catsxp_ads
