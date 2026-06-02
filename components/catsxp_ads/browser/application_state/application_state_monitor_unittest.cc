/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/browser/application_state/application_state_monitor.h"

#include <string>

#include "catsxp/components/catsxp_ads/browser/application_state/test/test_application_state_observer.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsApplicationStateMonitorTest : public testing::Test,
                                            public ApplicationStateMonitor {
 protected:
  TestApplicationStateObserver application_state_observer_;
};

TEST_F(CatsxpAdsApplicationStateMonitorTest,
       IsBrowserActiveReturnsTrueByDefault) {
  // Act & Assert
  EXPECT_TRUE(IsBrowserActive());
}

TEST_F(CatsxpAdsApplicationStateMonitorTest,
       NotifiesObserverWhenBrowserEntersForeground) {
  // Arrange
  AddObserver(&application_state_observer_);

  // Act
  NotifyBrowserDidBecomeActive();

  // Assert
  EXPECT_EQ(1U, application_state_observer_.foreground_count());
  EXPECT_EQ(0U, application_state_observer_.background_count());

  RemoveObserver(&application_state_observer_);
}

TEST_F(CatsxpAdsApplicationStateMonitorTest,
       NotifiesObserverWhenBrowserEntersBackground) {
  // Arrange
  AddObserver(&application_state_observer_);

  // Act
  NotifyBrowserDidResignActive();

  // Assert
  EXPECT_EQ(0U, application_state_observer_.foreground_count());
  EXPECT_EQ(1U, application_state_observer_.background_count());

  RemoveObserver(&application_state_observer_);
}

TEST_F(CatsxpAdsApplicationStateMonitorTest, DoesNotNotifyObserverAfterRemoval) {
  // Arrange
  AddObserver(&application_state_observer_);
  RemoveObserver(&application_state_observer_);

  // Act
  NotifyBrowserDidBecomeActive();
  NotifyBrowserDidResignActive();

  // Assert
  EXPECT_EQ(0U, application_state_observer_.foreground_count());
  EXPECT_EQ(0U, application_state_observer_.background_count());
}

TEST_F(CatsxpAdsApplicationStateMonitorTest,
       NotifiesAllObserversOnForegroundTransition) {
  // Arrange
  TestApplicationStateObserver application_state_observer_1;
  AddObserver(&application_state_observer_1);
  TestApplicationStateObserver application_state_observer_2;
  AddObserver(&application_state_observer_2);

  // Act
  NotifyBrowserDidBecomeActive();

  // Assert
  EXPECT_EQ(1U, application_state_observer_1.foreground_count());
  EXPECT_EQ(1U, application_state_observer_2.foreground_count());

  RemoveObserver(&application_state_observer_1);
  RemoveObserver(&application_state_observer_2);
}

TEST_F(CatsxpAdsApplicationStateMonitorTest,
       NotifiesAllObserversOnBackgroundTransition) {
  // Arrange
  TestApplicationStateObserver application_state_observer_1;
  AddObserver(&application_state_observer_1);
  TestApplicationStateObserver application_state_observer_2;
  AddObserver(&application_state_observer_2);

  // Act
  NotifyBrowserDidResignActive();

  // Assert
  EXPECT_EQ(1U, application_state_observer_1.background_count());
  EXPECT_EQ(1U, application_state_observer_2.background_count());

  RemoveObserver(&application_state_observer_1);
  RemoveObserver(&application_state_observer_2);
}

}  // namespace catsxp_ads
