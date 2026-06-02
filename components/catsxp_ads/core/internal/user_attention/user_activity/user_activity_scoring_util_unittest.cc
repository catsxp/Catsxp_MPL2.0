/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_scoring_util.h"

#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_manager.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsUserActivityScoringUtilTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    scoped_feature_list_.InitAndEnableFeatureWithParameters(
        kUserActivityFeature, {{"triggers", "0D=1.0;08=1.0"},
                               {"time_window", "1h"},
                               {"threshold", "2.0"}});
  }

  base::test::ScopedFeatureList scoped_feature_list_;
};

TEST_F(CatsxpAdsUserActivityScoringUtilTest, WasUserActive) {
  // Arrange
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClosedTab);

  // Act & Assert
  EXPECT_TRUE(WasUserActive());
}

TEST_F(CatsxpAdsUserActivityScoringUtilTest, WasUserInactive) {
  // Act & Assert
  EXPECT_FALSE(WasUserActive());
}

TEST_F(CatsxpAdsUserActivityScoringUtilTest, WasUserInactiveIfBelowThreshold) {
  // Arrange
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);

  // Act & Assert
  EXPECT_FALSE(WasUserActive());
}

TEST_F(CatsxpAdsUserActivityScoringUtilTest,
       WasUserInactiveAfterTimeWindowHasElapsed) {
  // Arrange
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClosedTab);

  AdvanceClockBy(kUserActivityTimeWindow.Get() + base::Milliseconds(1));

  // Act & Assert
  EXPECT_FALSE(WasUserActive());
}

}  // namespace catsxp_ads
