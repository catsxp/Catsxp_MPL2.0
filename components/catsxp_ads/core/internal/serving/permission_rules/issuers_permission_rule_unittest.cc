/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/issuers_permission_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/test/issuers_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsIssuersPermissionRuleTest : public test::TestBase {};

TEST_F(CatsxpAdsIssuersPermissionRuleTest, ShouldAllowForRewardsUser) {
  // Arrange
  test::BuildAndSetIssuers();

  // Act & Assert
  EXPECT_TRUE(HasIssuersPermission());
}

TEST_F(CatsxpAdsIssuersPermissionRuleTest, ShouldAlwaysAllowForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  EXPECT_TRUE(HasIssuersPermission());
}

TEST_F(CatsxpAdsIssuersPermissionRuleTest, ShouldNotAllowIfNoIssuers) {
  // Act & Assert
  EXPECT_FALSE(HasIssuersPermission());
}

}  // namespace catsxp_ads
