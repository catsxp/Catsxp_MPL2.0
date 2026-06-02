/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_util.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_manager.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_trigger_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsUserActivityUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsUserActivityUtilTest, GetNumberOfUserActivityEvents) {
  // Arrange
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);

  AdvanceClockBy(base::Minutes(30));

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClosedTab);

  AdvanceClockBy(base::Minutes(5));

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Minutes(30));

  // Act
  const size_t number_of_user_activity_events = GetNumberOfUserActivityEvents(
      events, UserActivityEventType::kClickedLink);

  // Assert
  EXPECT_EQ(2U, number_of_user_activity_events);
}

TEST_F(CatsxpAdsUserActivityUtilTest,
       GetNumberOfUserActivityEventsForMissingEvent) {
  // Arrange
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Minutes(30));

  // Act
  const size_t number_of_user_activity_events =
      GetNumberOfUserActivityEvents(events, UserActivityEventType::kClosedTab);

  // Assert
  EXPECT_EQ(0U, number_of_user_activity_events);
}

TEST_F(CatsxpAdsUserActivityUtilTest,
       GetNumberOfUserActivityEventsFromEmptyHistory) {
  // Arrange
  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Minutes(30));

  // Act
  const size_t number_of_user_activity_events =
      GetNumberOfUserActivityEvents(events, UserActivityEventType::kClosedTab);

  // Assert
  EXPECT_EQ(0U, number_of_user_activity_events);
}

TEST_F(CatsxpAdsUserActivityUtilTest, GetTimeSinceLastUserActivityEvent) {
  // Arrange
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStartedPlayingMedia);
  AdvanceClockBy(base::Minutes(30));

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStartedPlayingMedia);
  AdvanceClockBy(base::Minutes(5));

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStartedPlayingMedia);
  AdvanceClockBy(base::Minutes(5));

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  AdvanceClockBy(base::Minutes(1));

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Minutes(30));

  // Act
  const base::TimeDelta time_since_last_user_activity_event =
      GetTimeSinceLastUserActivityEvent(
          events, UserActivityEventType::kTabStartedPlayingMedia);

  // Assert
  EXPECT_EQ(base::Minutes(6), time_since_last_user_activity_event);
}

TEST_F(CatsxpAdsUserActivityUtilTest,
       GetTimeSinceLastUserActivityEventForMissingEvent) {
  // Arrange
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Minutes(30));

  // Act
  const base::TimeDelta time_since_last_user_activity_event =
      GetTimeSinceLastUserActivityEvent(
          events, UserActivityEventType::kTabStartedPlayingMedia);

  // Assert
  EXPECT_TRUE(time_since_last_user_activity_event.is_zero());
}

TEST_F(CatsxpAdsUserActivityUtilTest,
       GetTimeSinceLastUserActivityEventFromEmptyHistory) {
  // Arrange
  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Minutes(30));

  // Act
  const base::TimeDelta time_since_last_user_activity_event =
      GetTimeSinceLastUserActivityEvent(
          events, UserActivityEventType::kTabStartedPlayingMedia);

  // Assert
  EXPECT_TRUE(time_since_last_user_activity_event.is_zero());
}

TEST_F(CatsxpAdsUserActivityUtilTest, ToUserActivityTriggers) {
  // Act
  const UserActivityTriggerList user_activity_triggers = ToUserActivityTriggers(
      /*param_value=*/"05=.3;0C1305=1.0;0C13=0.5");

  // Assert
  UserActivityTriggerList expected_user_activity_triggers;
  UserActivityTriggerInfo expected_user_activity_trigger;
  expected_user_activity_trigger.event_sequence = "05";
  expected_user_activity_trigger.score = 0.3;
  expected_user_activity_triggers.push_back(expected_user_activity_trigger);
  expected_user_activity_trigger.event_sequence = "0C1305";
  expected_user_activity_trigger.score = 1.0;
  expected_user_activity_triggers.push_back(expected_user_activity_trigger);
  expected_user_activity_trigger.event_sequence = "0C13";
  expected_user_activity_trigger.score = 0.5;
  expected_user_activity_triggers.push_back(expected_user_activity_trigger);
  EXPECT_EQ(expected_user_activity_triggers, user_activity_triggers);
}

TEST_F(CatsxpAdsUserActivityUtilTest, ToUserActivityTriggersForInvalidTrigger) {
  // Act
  const UserActivityTriggerList user_activity_triggers = ToUserActivityTriggers(
      /*param_value=*/"INVALID");

  // Assert
  EXPECT_THAT(user_activity_triggers, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsUserActivityUtilTest,
       ToUserActivityTriggersForMalformedTrigger) {
  // Act
  const UserActivityTriggerList user_activity_triggers = ToUserActivityTriggers(
      /*param_value=*/"05=.3;0C1305=;=0.5;C1305=1.0");

  // Assert
  UserActivityTriggerList expected_user_activity_triggers;
  UserActivityTriggerInfo expected_user_activity_trigger;
  expected_user_activity_trigger.event_sequence = "05";
  expected_user_activity_trigger.score = 0.3;
  expected_user_activity_triggers.push_back(expected_user_activity_trigger);
  EXPECT_EQ(expected_user_activity_triggers, user_activity_triggers);
}

TEST_F(CatsxpAdsUserActivityUtilTest, ToUserActivityTriggersForEmptyTrigger) {
  // Act
  const UserActivityTriggerList user_activity_triggers = ToUserActivityTriggers(
      /*param_value=*/"");

  // Assert
  EXPECT_THAT(user_activity_triggers, ::testing::IsEmpty());
}

}  // namespace catsxp_ads
