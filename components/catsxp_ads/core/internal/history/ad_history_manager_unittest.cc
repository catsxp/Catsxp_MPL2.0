/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/history/ad_history_manager.h"

#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/test/search_result_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/new_tab_page_ad_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/test/creative_new_tab_page_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/notification_ad_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/test/creative_notification_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/history/ad_history_builder_util.h"
#include "catsxp/components/catsxp_ads/core/internal/history/ad_history_manager_observer.h"
#include "catsxp/components/catsxp_ads/core/internal/history/test/ad_history_manager_observer_mock.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_info.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/notification_ad/notification_ad_info.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsAdHistoryManagerTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    observation_.Observe(&AdHistoryManager::GetInstance());
  }

  AdHistoryManagerObserverMock history_manager_observer_mock_;
  base::ScopedObservation<AdHistoryManager, AdHistoryManagerObserver>
      observation_{&history_manager_observer_mock_};
};

TEST_F(CatsxpAdsAdHistoryManagerTest, AddNotificationAdHistory) {
  // Arrange
  const CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  const NotificationAdInfo ad = BuildNotificationAd(creative_ad);

  // Act & Assert
  const AdHistoryItemInfo expected_ad_history_item = BuildAdHistoryItem(
      ad, mojom::ConfirmationType::kViewedImpression, ad.title, ad.body);
  EXPECT_CALL(history_manager_observer_mock_,
              OnDidAddAdHistoryItem(expected_ad_history_item));
  AdHistoryManager::GetInstance().Add(
      ad, mojom::ConfirmationType::kViewedImpression);
}

TEST_F(CatsxpAdsAdHistoryManagerTest,
       DoNotAddNotificationAdHistoryForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  const CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  const NotificationAdInfo ad = BuildNotificationAd(creative_ad);

  // Act & Assert
  EXPECT_CALL(history_manager_observer_mock_, OnDidAddAdHistoryItem).Times(0);
  AdHistoryManager::GetInstance().Add(
      ad, mojom::ConfirmationType::kViewedImpression);
}

TEST_F(CatsxpAdsAdHistoryManagerTest, AddNewTabPageAdHistory) {
  // Arrange
  const CreativeNewTabPageAdInfo creative_ad =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);
  const NewTabPageAdInfo ad = BuildNewTabPageAd(creative_ad);

  // Act & Assert
  const AdHistoryItemInfo expected_ad_history_item = BuildAdHistoryItem(
      ad, mojom::ConfirmationType::kViewedImpression, ad.company_name, ad.alt);
  EXPECT_CALL(history_manager_observer_mock_,
              OnDidAddAdHistoryItem(expected_ad_history_item));
  AdHistoryManager::GetInstance().Add(
      ad, mojom::ConfirmationType::kViewedImpression);
}

TEST_F(CatsxpAdsAdHistoryManagerTest,
       DoNotAddNewTabPageAdHistoryForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  const CreativeNewTabPageAdInfo creative_ad =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);
  const NewTabPageAdInfo ad = BuildNewTabPageAd(creative_ad);

  // Act & Assert
  EXPECT_CALL(history_manager_observer_mock_, OnDidAddAdHistoryItem).Times(0);
  AdHistoryManager::GetInstance().Add(
      ad, mojom::ConfirmationType::kViewedImpression);
}

TEST_F(CatsxpAdsAdHistoryManagerTest, AddSearchResultAdHistory) {
  // Arrange
  const SearchResultAdInfo ad =
      test::BuildSearchResultAd(/*use_random_uuids=*/true);

  // Act & Assert
  const AdHistoryItemInfo expected_ad_history_item =
      BuildAdHistoryItem(ad, mojom::ConfirmationType::kViewedImpression,
                         ad.headline_text, ad.description);
  EXPECT_CALL(history_manager_observer_mock_,
              OnDidAddAdHistoryItem(expected_ad_history_item));
  AdHistoryManager::GetInstance().Add(
      ad, mojom::ConfirmationType::kViewedImpression);
}

TEST_F(CatsxpAdsAdHistoryManagerTest,
       DoNotAddSearchResultAdHistoryForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  const SearchResultAdInfo ad =
      test::BuildSearchResultAd(/*use_random_uuids=*/true);

  // Act & Assert
  EXPECT_CALL(history_manager_observer_mock_, OnDidAddAdHistoryItem).Times(0);
  AdHistoryManager::GetInstance().Add(
      ad, mojom::ConfirmationType::kViewedImpression);
}

}  // namespace catsxp_ads
