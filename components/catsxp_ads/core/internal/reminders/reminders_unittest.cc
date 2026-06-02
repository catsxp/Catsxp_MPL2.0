/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "base/memory/raw_ptr.h"
#include "base/test/scoped_feature_list.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/test/confirmation_type_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/notification_ad_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/test/creative_notification_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/history/ad_history_database_util.h"
#include "catsxp/components/catsxp_ads/core/internal/history/ad_history_manager.h"
#include "catsxp/components/catsxp_ads/core/internal/history/test/ad_history_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/reminders/reminders_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/reminders/reminders_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/test/ads_observer_mock.h"
#include "catsxp/components/catsxp_ads/core/internal/test/ads_observer_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/notification_ad/notification_ad_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

void BuildAndSaveAdHistory(mojom::AdType mojom_ad_type, size_t clicked_count) {
  const std::vector<mojom::ConfirmationType> mojom_confirmation_types =
      test::BuildConfirmationTypeForCountAndIntersperseOtherTypes(
          mojom::ConfirmationType::kClicked, clicked_count);

  const AdHistoryList ad_history =
      test::BuildAdHistory(mojom_ad_type, mojom_confirmation_types,
                           /*use_random_uuids=*/false);

  database::SaveAdHistory(ad_history);
}

}  // namespace

class CatsxpAdsRemindersTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    ads_observer_mock_ = test::SetUpAdsObserverMock();
  }

  raw_ptr<AdsObserverMock> ads_observer_mock_ = nullptr;  // Not owned.
};

TEST_F(CatsxpAdsRemindersTest,
       DoNotShowUserClickTheSameAdMultipleTimesReminderForAndroid) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  fake_operating_system_.SetType(OperatingSystemType::kAndroid);
  OperatingSystem::SetForTesting(&fake_operating_system_);

  BuildAndSaveAdHistory(
      mojom::AdType::kNotificationAd,
      /*clicked_count=*/kRemindUserIfClickingTheSameAdAfter.Get() - 1);

  const NotificationAdInfo ad =
      BuildNotificationAd(test::BuildCreativeNotificationAd(
          /*use_random_uuids=*/false));

  // Act & Assert
  EXPECT_CALL(*ads_observer_mock_, OnRemindUser).Times(0);
  AdHistoryManager::GetInstance().Add(ad, mojom::ConfirmationType::kClicked);
  FastForwardClockBy(kMaybeShowReminderAfter);
}

TEST_F(CatsxpAdsRemindersTest,
       DoNotShowUserClickTheSameAdMultipleTimesReminderForIOS) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  fake_operating_system_.SetType(OperatingSystemType::kIOS);
  OperatingSystem::SetForTesting(&fake_operating_system_);

  BuildAndSaveAdHistory(
      mojom::AdType::kNotificationAd,
      /*clicked_count=*/kRemindUserIfClickingTheSameAdAfter.Get() - 1);

  const NotificationAdInfo ad =
      BuildNotificationAd(test::BuildCreativeNotificationAd(
          /*use_random_uuids=*/false));

  // Act & Assert
  EXPECT_CALL(*ads_observer_mock_, OnRemindUser).Times(0);
  AdHistoryManager::GetInstance().Add(ad, mojom::ConfirmationType::kClicked);
  FastForwardClockBy(kMaybeShowReminderAfter);
}

TEST_F(CatsxpAdsRemindersTest,
       ShowReminderWhenUserClicksTheSameAdMultipleTimesForWindows) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  fake_operating_system_.SetType(OperatingSystemType::kWindows);
  OperatingSystem::SetForTesting(&fake_operating_system_);

  BuildAndSaveAdHistory(
      mojom::AdType::kNotificationAd,
      /*clicked_count=*/kRemindUserIfClickingTheSameAdAfter.Get() - 1);

  const NotificationAdInfo ad =
      BuildNotificationAd(test::BuildCreativeNotificationAd(
          /*use_random_uuids=*/false));

  // Act & Assert
  EXPECT_CALL(*ads_observer_mock_,
              OnRemindUser(mojom::ReminderType::kClickedSameAdMultipleTimes));
  AdHistoryManager::GetInstance().Add(ad, mojom::ConfirmationType::kClicked);
  FastForwardClockBy(kMaybeShowReminderAfter);
}

TEST_F(CatsxpAdsRemindersTest,
       ShowReminderWhenUserClicksTheSameAdMultipleTimesForMacOs) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  fake_operating_system_.SetType(OperatingSystemType::kMacOS);
  OperatingSystem::SetForTesting(&fake_operating_system_);

  BuildAndSaveAdHistory(
      mojom::AdType::kNotificationAd,
      /*clicked_count=*/kRemindUserIfClickingTheSameAdAfter.Get() - 1);

  const NotificationAdInfo ad =
      BuildNotificationAd(test::BuildCreativeNotificationAd(
          /*use_random_uuids=*/false));

  // Act & Assert
  EXPECT_CALL(*ads_observer_mock_,
              OnRemindUser(mojom::ReminderType::kClickedSameAdMultipleTimes));
  AdHistoryManager::GetInstance().Add(ad, mojom::ConfirmationType::kClicked);
  FastForwardClockBy(kMaybeShowReminderAfter);
}

TEST_F(CatsxpAdsRemindersTest,
       ShowReminderWhenUserClicksTheSameAdMultipleTimesForLinux) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  fake_operating_system_.SetType(OperatingSystemType::kLinux);
  OperatingSystem::SetForTesting(&fake_operating_system_);

  BuildAndSaveAdHistory(
      mojom::AdType::kNotificationAd,
      /*clicked_count=*/kRemindUserIfClickingTheSameAdAfter.Get() - 1);

  const NotificationAdInfo ad =
      BuildNotificationAd(test::BuildCreativeNotificationAd(
          /*use_random_uuids=*/false));

  // Act & Assert
  EXPECT_CALL(*ads_observer_mock_,
              OnRemindUser(mojom::ReminderType::kClickedSameAdMultipleTimes));
  AdHistoryManager::GetInstance().Add(ad, mojom::ConfirmationType::kClicked);
  FastForwardClockBy(kMaybeShowReminderAfter);
}

TEST_F(CatsxpAdsRemindersTest,
       DoNotShowReminderIfUserDoesNotClickTheSameAdMultipleTimes) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  BuildAndSaveAdHistory(
      mojom::AdType::kNotificationAd,
      /*clicked_count=*/kRemindUserIfClickingTheSameAdAfter.Get() - 2);

  const NotificationAdInfo ad =
      BuildNotificationAd(test::BuildCreativeNotificationAd(
          /*use_random_uuids=*/false));

  // Act & Assert
  EXPECT_CALL(*ads_observer_mock_, OnRemindUser).Times(0);
  AdHistoryManager::GetInstance().Add(ad, mojom::ConfirmationType::kClicked);
  FastForwardClockBy(kMaybeShowReminderAfter);
}

TEST_F(
    CatsxpAdsRemindersTest,
    DoNotShowReminderIfUserDoesNotClickTheSameAdMultipleTimesIfRemindersFeatureIsDisabled) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndDisableFeature(kRemindersFeature);

  BuildAndSaveAdHistory(
      mojom::AdType::kNotificationAd,
      /*clicked_count=*/kRemindUserIfClickingTheSameAdAfter.Get() - 1);

  const NotificationAdInfo ad =
      BuildNotificationAd(test::BuildCreativeNotificationAd(
          /*use_random_uuids=*/false));

  // Act & Assert
  EXPECT_CALL(*ads_observer_mock_, OnRemindUser).Times(0);
  AdHistoryManager::GetInstance().Add(ad, mojom::ConfirmationType::kClicked);
  FastForwardClockBy(kMaybeShowReminderAfter);
}

}  // namespace catsxp_ads
