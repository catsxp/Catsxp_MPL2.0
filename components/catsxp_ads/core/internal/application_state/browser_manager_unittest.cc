/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/application_state/browser_manager.h"

#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/internal/application_state/browser_manager_observer.h"
#include "catsxp/components/catsxp_ads/core/internal/application_state/test/browser_manager_observer_mock.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/mock_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsBrowserManagerTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    observation_.Observe(&BrowserManager::GetInstance());
  }

  BrowserManagerObserverMock browser_manager_observer_mock_;
  base::ScopedObservation<BrowserManager, BrowserManagerObserver> observation_{
      &browser_manager_observer_mock_};
};

TEST_F(CatsxpAdsBrowserManagerTest, OnNotifyBrowserDidBecomeActive) {
  // Arrange
  EXPECT_CALL(browser_manager_observer_mock_, OnBrowserDidBecomeActive);

  // Act
  ads_client_notifier_.NotifyBrowserDidBecomeActive();

  // Assert
  EXPECT_TRUE(BrowserManager::GetInstance().IsActive());
}

TEST_F(CatsxpAdsBrowserManagerTest, OnNotifyBrowserDidResignActive) {
  // Arrange
  ads_client_notifier_.NotifyBrowserDidBecomeActive();

  EXPECT_CALL(browser_manager_observer_mock_, OnBrowserDidResignActive);

  // Act
  ads_client_notifier_.NotifyBrowserDidResignActive();

  // Assert
  EXPECT_FALSE(BrowserManager::GetInstance().IsActive());
}

TEST_F(CatsxpAdsBrowserManagerTest, OnNotifyBrowserDidEnterForeground) {
  // Arrange
  EXPECT_CALL(browser_manager_observer_mock_, OnBrowserDidEnterForeground);

  // Act
  ads_client_notifier_.NotifyBrowserDidEnterForeground();

  // Assert
  EXPECT_TRUE(BrowserManager::GetInstance().IsInForeground());
}

TEST_F(CatsxpAdsBrowserManagerTest, OnNotifyBrowserDidEnterBackground) {
  // Arrange
  ads_client_notifier_.NotifyBrowserDidEnterForeground();

  EXPECT_CALL(browser_manager_observer_mock_, OnBrowserDidEnterBackground);

  // Act
  ads_client_notifier_.NotifyBrowserDidEnterBackground();

  // Assert
  EXPECT_FALSE(BrowserManager::GetInstance().IsInForeground());
}

TEST_F(CatsxpAdsBrowserManagerTest,
       OnNotifyDidInitializeAdsWhenBrowserIsActive) {
  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(BrowserManager::GetInstance().IsActive());
  EXPECT_TRUE(BrowserManager::GetInstance().IsInForeground());
}

TEST_F(CatsxpAdsBrowserManagerTest,
       OnNotifyDidInitializeAdsWhenBrowserIsInactive) {
  // Arrange
  test::MockIsBrowserActive(ads_client_mock_, false);

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_FALSE(BrowserManager::GetInstance().IsActive());
  EXPECT_FALSE(BrowserManager::GetInstance().IsInForeground());
}

}  // namespace catsxp_ads
