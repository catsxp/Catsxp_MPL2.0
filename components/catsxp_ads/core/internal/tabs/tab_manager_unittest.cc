/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/tabs/tab_manager.h"

#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/tabs/tab_manager_observer.h"
#include "catsxp/components/catsxp_ads/core/internal/tabs/test/tab_manager_observer_mock.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsTabManagerTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    observation_.Observe(&TabManager::GetInstance());
  }

  ::testing::StrictMock<TabManagerObserverMock> tab_manager_observer_mock_;
  base::ScopedObservation<TabManager, TabManagerObserver> observation_{
      &tab_manager_observer_mock_};
};

TEST_F(CatsxpAdsTabManagerTest, OpenNewTab) {
  // Act & Assert
  EXPECT_CALL(
      tab_manager_observer_mock_,
      OnDidOpenNewTab(TabInfo{/*id=*/1,
                              /*is_visible=*/true,
                              /*redirect_chain=*/{GURL("https://catsxp.com")},
                              /*is_playing_media=*/false}));
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);
}

TEST_F(CatsxpAdsTabManagerTest, DoNotChangeOccludedTabIfMatchingRedirectChain) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/false);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChange).Times(0);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/false);
}

TEST_F(CatsxpAdsTabManagerTest, DoNotChangeVisibleTabIfMatchingRedirectChain) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChange).Times(0);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);
}

TEST_F(CatsxpAdsTabManagerTest, DoNotNotifyForRestoredTabs) {
  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab).Times(0);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChange).Times(0);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus).Times(0);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/true, /*is_visible=*/true);
}

TEST_F(CatsxpAdsTabManagerTest,
       DoNotNotifyTabDidChangeIfReturningToPreviouslyCommittedNavigation) {
  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChange).Times(0);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/false, /*is_restoring=*/true, /*is_visible=*/true);
}

TEST_F(CatsxpAdsTabManagerTest, ChangeTabFocusToOccluded) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus(/*tab_id=*/1));
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/false);
}

TEST_F(CatsxpAdsTabManagerTest, ChangeTabFocusToVisible) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/false);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus(/*tab_id=*/1));
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);
}

TEST_F(CatsxpAdsTabManagerTest, ChangeOccudedTabIfMismatchingRedirectChain) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/false);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_,
              OnTabDidChange(TabInfo{
                  /*id=*/1,
                  /*is_visible=*/false,
                  /*redirect_chain=*/{GURL("https://basicattentiontoken.org")},
                  /*is_playing_media=*/
                  false}));
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://basicattentiontoken.org")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/false);
}

TEST_F(CatsxpAdsTabManagerTest, ChangeVisibleTabIfMismatchingRedirectChain) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_,
              OnTabDidChange(TabInfo{
                  /*id=*/1,
                  /*is_visible=*/true,
                  /*redirect_chain=*/{GURL("https://basicattentiontoken.org")},
                  /*is_playing_media=*/
                  false}));
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://basicattentiontoken.org")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);
}

TEST_F(CatsxpAdsTabManagerTest, CloseTab) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_, OnDidCloseTab(/*tab_id=*/1));
  ads_client_notifier_.NotifyDidCloseTab(/*tab_id=*/1);
}

TEST_F(CatsxpAdsTabManagerTest, IsPlayingMedia) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  EXPECT_CALL(tab_manager_observer_mock_,
              OnTabDidStartPlayingMedia(/*tab_id=*/1));
  ads_client_notifier_.NotifyTabDidStartPlayingMedia(/*tab_id=*/1);

  // Act & Assert
  EXPECT_TRUE(TabManager::GetInstance().IsPlayingMedia(/*tab_id=*/1));
}

TEST_F(CatsxpAdsTabManagerTest, IsNotPlayingMedia) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  EXPECT_FALSE(TabManager::GetInstance().IsPlayingMedia(/*tab_id=*/1));
}

TEST_F(CatsxpAdsTabManagerTest, StartPlayingMedia) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_,
              OnTabDidStartPlayingMedia(/*tab_id=*/1));
  ads_client_notifier_.NotifyTabDidStartPlayingMedia(/*tab_id=*/1);
}

TEST_F(CatsxpAdsTabManagerTest, DoNotStartPlayingMediaIfAlreadyPlaying) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false,
      /*is_visible=*/true);
  EXPECT_CALL(tab_manager_observer_mock_,
              OnTabDidStartPlayingMedia(/*tab_id=*/1));
  ads_client_notifier_.NotifyTabDidStartPlayingMedia(/*tab_id=*/1);

  // Act & Assert
  ads_client_notifier_.NotifyTabDidStartPlayingMedia(/*tab_id=*/1);
}

TEST_F(CatsxpAdsTabManagerTest, StopPlayingMedia) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  EXPECT_CALL(tab_manager_observer_mock_,
              OnTabDidStartPlayingMedia(/*tab_id=*/1));
  ads_client_notifier_.NotifyTabDidStartPlayingMedia(/*tab_id=*/1);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_,
              OnTabDidStopPlayingMedia(/*tab_id=*/1));
  ads_client_notifier_.NotifyTabDidStopPlayingMedia(/*tab_id=*/1);
}

TEST_F(CatsxpAdsTabManagerTest, GetVisibleTab) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  const TabInfo tab{/*id=*/1, /*is_visible=*/true,
                    /*redirect_chain=*/{GURL("https://catsxp.com")},
                    /*is_playing_media=*/
                    false};
  EXPECT_EQ(tab, TabManager::GetInstance().MaybeGetVisible());
}

TEST_F(CatsxpAdsTabManagerTest, DoNotGetVisibleTabIfNoTabs) {
  // Act & Assert
  EXPECT_FALSE(TabManager::GetInstance().MaybeGetVisible());
}

TEST_F(CatsxpAdsTabManagerTest, GetTabForId) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/2,
      /*redirect_chain=*/{GURL("https://basicattentiontoken.org")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  const TabInfo tab{
      /*id=*/2, /*is_visible=*/true,
      /*redirect_chain=*/{GURL("https://basicattentiontoken.org")},
      /*is_playing_media=*/
      false};
  EXPECT_EQ(tab, TabManager::GetInstance().MaybeGetForId(2));
}

TEST_F(CatsxpAdsTabManagerTest, DoNotGetIfMissingTab) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  EXPECT_FALSE(TabManager::GetInstance().MaybeGetForId(2));
}

TEST_F(CatsxpAdsTabManagerTest, DoNotGetIfNoTabs) {
  // Act & Assert
  EXPECT_FALSE(TabManager::GetInstance().MaybeGetForId(1));
}

}  // namespace catsxp_ads
