/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/reminders/reminder/clicked_same_ad_multiple_times_reminder_util.h"

#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/test/confirmation_type_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/history/test/ad_history_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/reminders/reminders_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/test/ads_observer_mock.h"
#include "catsxp/components/catsxp_ads/core/internal/test/ads_observer_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsClickedSameAdMultipleTimesReminderUtilTest
    : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    ads_observer_mock_ = test::SetUpAdsObserverMock();
  }

  raw_ptr<AdsObserverMock> ads_observer_mock_ = nullptr;  // Not owned.
};

TEST_F(CatsxpAdsClickedSameAdMultipleTimesReminderUtilTest, ShouldRemindUser) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  // Act & Assert
  EXPECT_TRUE(ShouldRemindUser());
}

TEST_F(CatsxpAdsClickedSameAdMultipleTimesReminderUtilTest,
       ShouldNotRemindUserWhenRemindersFeatureIsDisabled) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndDisableFeature(kRemindersFeature);

  // Act & Assert
  EXPECT_FALSE(ShouldRemindUser());
}

TEST_F(CatsxpAdsClickedSameAdMultipleTimesReminderUtilTest,
       ShouldNotRemindUser) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kRemindersFeature, {{"remind_user_if_clicking_the_same_ad_after", "0"}});

  // Act & Assert
  EXPECT_FALSE(ShouldRemindUser());
}

TEST_F(CatsxpAdsClickedSameAdMultipleTimesReminderUtilTest,
       UserClickedTheSameAdMultipleTimes) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  const AdHistoryList ad_history = test::BuildAdHistoryForSamePlacement(
      mojom::AdType::kNotificationAd,
      test::BuildConfirmationTypeForCountAndIntersperseOtherTypes(
          mojom::ConfirmationType::kClicked,
          /*count=*/kRemindUserIfClickingTheSameAdAfter.Get()),
      /*use_random_uuids=*/false);

  // Act & Assert
  EXPECT_TRUE(DidUserClickTheSameAdMultipleTimes(test::kCreativeInstanceId,
                                                 ad_history));
}

TEST_F(CatsxpAdsClickedSameAdMultipleTimesReminderUtilTest,
       UserDidNotClickTheSameAdMultipleTimes) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  const AdHistoryList ad_history = test::BuildAdHistoryForSamePlacement(
      mojom::AdType::kNotificationAd,
      test::BuildConfirmationTypeForCountAndIntersperseOtherTypes(
          mojom::ConfirmationType::kClicked,
          /*count=*/kRemindUserIfClickingTheSameAdAfter.Get() - 1),
      /*use_random_uuids=*/false);

  // Act & Assert
  EXPECT_FALSE(DidUserClickTheSameAdMultipleTimes(test::kCreativeInstanceId,
                                                  ad_history));
}

TEST_F(CatsxpAdsClickedSameAdMultipleTimesReminderUtilTest,
       UserClickedTheSameAdMultipleTimesConsecutively) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  const AdHistoryList ad_history = test::BuildAdHistoryForSamePlacement(
      mojom::AdType::kNotificationAd,
      test::BuildConfirmationTypeForCountAndIntersperseOtherTypes(
          mojom::ConfirmationType::kClicked,
          /*count=*/kRemindUserIfClickingTheSameAdAfter.Get() * 2),
      /*use_random_uuids=*/false);

  // Act & Assert
  EXPECT_TRUE(DidUserClickTheSameAdMultipleTimes(test::kCreativeInstanceId,
                                                 ad_history));
}

TEST_F(CatsxpAdsClickedSameAdMultipleTimesReminderUtilTest,
       UserDidNotClickTheSameAdMultipleTimesConsecutively) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  const AdHistoryList ad_history = test::BuildAdHistoryForSamePlacement(
      mojom::AdType::kNotificationAd,
      test::BuildConfirmationTypeForCountAndIntersperseOtherTypes(
          mojom::ConfirmationType::kClicked,
          /*count=*/(kRemindUserIfClickingTheSameAdAfter.Get() * 2) - 1),
      /*use_random_uuids=*/false);

  // Act & Assert
  EXPECT_FALSE(DidUserClickTheSameAdMultipleTimes(test::kCreativeInstanceId,
                                                  ad_history));
}

TEST_F(CatsxpAdsClickedSameAdMultipleTimesReminderUtilTest,
       UserClickedDifferentAdsMultipleTimes) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  const AdHistoryList ad_history = test::BuildAdHistoryForSamePlacement(
      mojom::AdType::kNotificationAd,
      test::BuildConfirmationTypeForCountAndIntersperseOtherTypes(
          mojom::ConfirmationType::kClicked,
          /*count=*/kRemindUserIfClickingTheSameAdAfter.Get()),
      /*use_random_uuids=*/true);

  // Act & Assert
  EXPECT_FALSE(DidUserClickTheSameAdMultipleTimes(test::kCreativeInstanceId,
                                                  ad_history));
}

TEST_F(CatsxpAdsClickedSameAdMultipleTimesReminderUtilTest,
       RemindUserTheyDoNotNeedToClickToEarnRewards) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  // Act & Assert
  EXPECT_CALL(*ads_observer_mock_,
              OnRemindUser(mojom::ReminderType::kClickedSameAdMultipleTimes));
  RemindUserTheyDoNotNeedToClickToEarnRewards();
}

TEST_F(CatsxpAdsClickedSameAdMultipleTimesReminderUtilTest,
       RemindUserMultipleTimesTheyDoNotNeedToClickToEarnRewards) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  RemindUserTheyDoNotNeedToClickToEarnRewards();

  // Act & Assert
  EXPECT_CALL(*ads_observer_mock_,
              OnRemindUser(mojom::ReminderType::kClickedSameAdMultipleTimes));
  RemindUserTheyDoNotNeedToClickToEarnRewards();
}

}  // namespace catsxp_ads
