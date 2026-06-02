/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_scoring.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_manager.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_trigger_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsUserActivityScoringTest : public test::TestBase {};

TEST_F(CatsxpAdsUserActivityScoringTest, GetUserActivityScore) {
  // Arrange
  const UserActivityTriggerList triggers =
      ToUserActivityTriggers("06=.3;0D1406=1.0;0D14=0.5");

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedReloadButton);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStartedPlayingMedia);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Hours(1));

  // Act & Assert
  EXPECT_EQ(1.8, GetUserActivityScore(triggers, events));
}

TEST_F(CatsxpAdsUserActivityScoringTest, GetUserActivityScoreForTimeWindow) {
  // Arrange
  const UserActivityTriggerList triggers =
      ToUserActivityTriggers("06=.3;0D1406=1.0;0D14=0.5");

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  AdvanceClockBy(base::Hours(2));
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedReloadButton);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStartedPlayingMedia);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Hours(1));

  // Act & Assert
  EXPECT_EQ(1.5, GetUserActivityScore(triggers, events));
}

TEST_F(CatsxpAdsUserActivityScoringTest,
       GetUserActivityScoreForInvalidEventSequence) {
  // Arrange
  const UserActivityTriggerList triggers = ToUserActivityTriggers("INVALID");

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedReloadButton);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStartedPlayingMedia);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Hours(1));

  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, GetUserActivityScore(triggers, events));
}

TEST_F(CatsxpAdsUserActivityScoringTest,
       GetUserActivityScoreForMalformedEventSequence) {
  // Arrange
  const UserActivityTriggerList triggers =
      ToUserActivityTriggers("06=1;0D1406=1.0;=0.5");

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedReloadButton);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStartedPlayingMedia);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Hours(1));

  // Act & Assert
  EXPECT_EQ(2.0, GetUserActivityScore(triggers, events));
}

TEST_F(CatsxpAdsUserActivityScoringTest,
       GetUserActivityScoreForMixedCaseEventSequence) {
  // Arrange
  const UserActivityTriggerList triggers =
      ToUserActivityTriggers("06=.3;0d1406=1.0;0D14=0.5");

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedReloadButton);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStartedPlayingMedia);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Hours(1));

  // Act & Assert
  EXPECT_EQ(1.8, GetUserActivityScore(triggers, events));
}

TEST_F(
    CatsxpAdsUserActivityScoringTest,
    GetUserActivityScoreMatchesLongerTriggerEvenWhenShorterSuffixTriggerHasHigherScore) {
  // Arrange
  const UserActivityTriggerList triggers =
      ToUserActivityTriggers("06=1.0;0D1406=0.3");

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);  // 0D
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);  // 14
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);  // 06

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Hours(1));

  // Act & Assert
  EXPECT_EQ(0.3, GetUserActivityScore(triggers, events));
}

TEST_F(CatsxpAdsUserActivityScoringTest,
       GetUserActivityScoreForEmptyEventSequence) {
  // Arrange
  const UserActivityTriggerList triggers =
      ToUserActivityTriggers(/*param_value=*/{});

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedReloadButton);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStartedPlayingMedia);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Hours(1));

  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, GetUserActivityScore(triggers, events));
}

}  // namespace catsxp_ads
