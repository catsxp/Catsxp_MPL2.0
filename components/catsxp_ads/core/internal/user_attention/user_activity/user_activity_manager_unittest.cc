/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_manager.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_feature.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

void ExpectThatUserActivityEventsMatch(
    UserActivityEventType user_activity_event_type) {
  UserActivityEventList user_activity_events;
  UserActivityEventInfo user_activity_event;
  user_activity_event.type = user_activity_event_type;
  user_activity_event.created_at = test::Now();
  user_activity_events.push_back(user_activity_event);

  EXPECT_THAT(UserActivityManager::GetInstance().GetHistoryForTimeWindow(
                  base::Hours(1)),
              ::testing::ElementsAreArray(user_activity_events));
}

}  // namespace

class CatsxpAdsUserActivityManagerTest : public test::TestBase {};

TEST_F(CatsxpAdsUserActivityManagerTest, RecordInitializedAdsEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kInitializedAds;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordBrowserDidEnterForegroundEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kBrowserDidEnterForeground;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordBrowserDidEnterBackgroundEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kBrowserDidEnterBackground;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest,
       RecordClickedBackOrForwardNavigationButtonsEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kClickedBackOrForwardNavigationButtons;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordClickedBookmarkEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kClickedBookmark;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordClickedHomePageButtonEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kClickedHomePageButton;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordClickedLinkEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kClickedLink;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordClickedReloadButtonEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kClickedReloadButton;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordClosedTabEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kClosedTab;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordFocusedOnExistingTabEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kTabChangedFocus;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordGeneratedKeywordEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kGeneratedKeyword;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordNewNavigationEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kNewNavigation;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest,
       RecordOpenedLinkFromExternalApplicationEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kOpenedLinkFromExternalApplication;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordOpenedNewTabEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kOpenedNewTab;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordPlayedMediaEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kTabStartedPlayingMedia;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordStoppedPlayingMediaEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kTabStoppedPlayingMedia;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordSubmittedFormEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kSubmittedForm;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordTabUpdatedEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kTabDidChange;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordTypedAndSelectedNonUrlEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kTypedAndSelectedNonUrl;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest,
       RecordTypedKeywordOtherThanDefaultSearchProviderEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kTypedKeywordOtherThanDefaultSearchProvider;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordTypedUrlEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kTypedUrl;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordUsedAddressBarEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kUsedAddressBar;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordBrowserDidBecomeActiveEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kBrowserDidBecomeActive;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, RecordBrowserDidResignActiveEvent) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kBrowserDidResignActive;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  ExpectThatUserActivityEventsMatch(user_activity_event_type);
}

TEST_F(CatsxpAdsUserActivityManagerTest, DoNotRecordEventForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kInitializedAds;

  // Act
  UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);

  // Assert
  EXPECT_THAT(UserActivityManager::GetInstance().GetHistoryForTimeWindow(
                  base::Hours(1)),
              ::testing::IsEmpty());
}

TEST_F(CatsxpAdsUserActivityManagerTest, GetHistoryForTimeWindow) {
  // Arrange
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kInitializedAds);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kBrowserDidBecomeActive);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kBrowserDidEnterBackground);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedBackOrForwardNavigationButtons);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedBookmark);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedHomePageButton);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedReloadButton);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClosedTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabChangedFocus);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kGeneratedKeyword);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kNewNavigation);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedLinkFromExternalApplication);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStartedPlayingMedia);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStoppedPlayingMedia);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kSubmittedForm);

  AdvanceClockBy(base::Hours(1));

  const base::Time now = test::Now();

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabDidChange);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedAndSelectedNonUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedKeywordOtherThanDefaultSearchProvider);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kUsedAddressBar);

  AdvanceClockBy(base::Hours(1));

  // Act & Assert
  UserActivityEventList expected_user_activity_events;

  UserActivityEventInfo expected_user_activity_event;

  expected_user_activity_event.type = UserActivityEventType::kTabDidChange;
  expected_user_activity_event.created_at = now;
  expected_user_activity_events.push_back(expected_user_activity_event);

  expected_user_activity_event.type =
      UserActivityEventType::kTypedAndSelectedNonUrl;
  expected_user_activity_event.created_at = now;
  expected_user_activity_events.push_back(expected_user_activity_event);

  expected_user_activity_event.type =
      UserActivityEventType::kTypedKeywordOtherThanDefaultSearchProvider;
  expected_user_activity_event.created_at = now;
  expected_user_activity_events.push_back(expected_user_activity_event);

  expected_user_activity_event.type = UserActivityEventType::kTypedUrl;
  expected_user_activity_event.created_at = now;
  expected_user_activity_events.push_back(expected_user_activity_event);

  expected_user_activity_event.type = UserActivityEventType::kUsedAddressBar;
  expected_user_activity_event.created_at = now;
  expected_user_activity_events.push_back(expected_user_activity_event);

  EXPECT_THAT(expected_user_activity_events,
              ::testing::ElementsAreArray(
                  UserActivityManager::GetInstance().GetHistoryForTimeWindow(
                      base::Hours(1))));
}

TEST_F(CatsxpAdsUserActivityManagerTest, MaximumHistoryItems) {
  // Arrange
  const UserActivityEventType user_activity_event_type =
      UserActivityEventType::kClosedTab;
  for (size_t i = 0; i < kMaximumUserActivityEvents.Get(); ++i) {
    UserActivityManager::GetInstance().RecordEvent(user_activity_event_type);
  }

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);

  // Act & Assert
  UserActivityEventList expected_user_activity_events;

  UserActivityEventInfo expected_user_activity_event;

  for (size_t i = 0; i < kMaximumUserActivityEvents.Get() - 1; ++i) {
    expected_user_activity_event.type = user_activity_event_type;
    expected_user_activity_event.created_at = test::Now();
    expected_user_activity_events.push_back(expected_user_activity_event);
  }

  expected_user_activity_event.type = UserActivityEventType::kOpenedNewTab;
  expected_user_activity_event.created_at = test::Now();
  expected_user_activity_events.push_back(expected_user_activity_event);

  EXPECT_THAT(expected_user_activity_events,
              ::testing::ElementsAreArray(
                  UserActivityManager::GetInstance().GetHistoryForTimeWindow(
                      base::Hours(1))));
}

}  // namespace catsxp_ads
