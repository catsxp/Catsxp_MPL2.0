/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/do_not_disturb_permission_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system_types.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsDoNotDisturbPermissionRuleTest : public test::TestBase {};

TEST_F(CatsxpAdsDoNotDisturbPermissionRuleTest,
       ShouldAllowWhileBrowserIsInactiveBetween6amAnd9pmOnAndroid) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kAndroid);

  ads_client_notifier_.NotifyBrowserDidResignActive();
  ads_client_notifier_.NotifyBrowserDidEnterBackground();

  AdvanceClockToLocalMidnight();

  // Act & Assert
  {
    // Verify 5:59 AM
    AdvanceClockBy(base::Hours(5) + base::Minutes(59));
    EXPECT_FALSE(HasDoNotDisturbPermission());
  }

  {
    // Verify 6:00 AM
    AdvanceClockBy(base::Minutes(1));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 8:59 PM
    AdvanceClockBy(base::Hours(14) + base::Minutes(59));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 9:00 PM
    AdvanceClockBy(base::Minutes(1));
    EXPECT_FALSE(HasDoNotDisturbPermission());
  }
}

TEST_F(CatsxpAdsDoNotDisturbPermissionRuleTest,
       ShouldAllowWhileBrowserIsActiveOnAndroid) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kAndroid);

  ads_client_notifier_.NotifyBrowserDidBecomeActive();
  ads_client_notifier_.NotifyBrowserDidEnterForeground();

  AdvanceClockToLocalMidnight();

  // Act & Assert
  {
    // Verify 5:59 AM
    AdvanceClockBy(base::Hours(5) + base::Minutes(59));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 6:00 AM
    AdvanceClockBy(base::Minutes(1));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 8:59 PM
    AdvanceClockBy(base::Hours(14) + base::Minutes(59));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 9:00 PM
    AdvanceClockBy(base::Minutes(1));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }
}

TEST_F(CatsxpAdsDoNotDisturbPermissionRuleTest, ShouldAlwaysAllowOnIOS) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kIOS);

  ads_client_notifier_.NotifyBrowserDidBecomeActive();
  ads_client_notifier_.NotifyBrowserDidEnterForeground();

  AdvanceClockToLocalMidnight();

  // Act & Assert
  {
    // Verify 00:00 AM
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 12:00 PM
    AdvanceClockBy(base::Hours(12));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }
}

TEST_F(CatsxpAdsDoNotDisturbPermissionRuleTest, ShouldAlwaysAllowOnMacOS) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kMacOS);

  ads_client_notifier_.NotifyBrowserDidBecomeActive();
  ads_client_notifier_.NotifyBrowserDidEnterForeground();

  AdvanceClockToLocalMidnight();

  // Act & Assert
  {
    // Verify 00:00 AM
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 12:00 PM
    AdvanceClockBy(base::Hours(12));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }
}

TEST_F(CatsxpAdsDoNotDisturbPermissionRuleTest, ShouldAlwaysAllowOnWindows) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kWindows);

  ads_client_notifier_.NotifyBrowserDidBecomeActive();
  ads_client_notifier_.NotifyBrowserDidEnterForeground();

  AdvanceClockToLocalMidnight();

  // Act & Assert
  {
    // Verify 00:00 AM
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 12:00 PM
    AdvanceClockBy(base::Hours(12));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }
}

TEST_F(CatsxpAdsDoNotDisturbPermissionRuleTest, ShouldAlwaysAllowOnLinux) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kLinux);

  ads_client_notifier_.NotifyBrowserDidBecomeActive();
  ads_client_notifier_.NotifyBrowserDidEnterForeground();

  AdvanceClockToLocalMidnight();

  // Act & Assert
  {
    // Verify 00:00 AM
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 12:00 PM
    AdvanceClockBy(base::Hours(12));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }
}

}  // namespace catsxp_ads
