/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/notification_ads/can_show_notifications_permission_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/mock_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsCanShowNotificationsPermissionRuleTest : public test::TestBase {};

TEST_F(CatsxpAdsCanShowNotificationsPermissionRuleTest, ShouldAllow) {
  // Act & Assert
  EXPECT_TRUE(HasCanShowNotificationsPermission());
}

TEST_F(CatsxpAdsCanShowNotificationsPermissionRuleTest, ShouldNotAllow) {
  // Arrange
  test::MockCanShowNotificationAds(ads_client_mock_, false);

  // Act & Assert
  EXPECT_FALSE(HasCanShowNotificationsPermission());
}

}  // namespace catsxp_ads
