/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/network_connection_permission_rule.h"

#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/mock_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/permission_rule_feature.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsNetworkConnectionPermissionRuleTest : public test::TestBase {};

TEST_F(CatsxpAdsNetworkConnectionPermissionRuleTest, ShouldAllow) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  // Act & Assert
  EXPECT_TRUE(HasNetworkConnectionPermission());
}

TEST_F(CatsxpAdsNetworkConnectionPermissionRuleTest, ShouldNotAllow) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  test::MockIsNetworkConnectionAvailable(ads_client_mock_, false);

  // Act & Assert
  EXPECT_FALSE(HasNetworkConnectionPermission());
}

TEST_F(CatsxpAdsNetworkConnectionPermissionRuleTest,
       ShouldAllowIfPermissionRuleIsDisabled) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kPermissionRulesFeature,
      {{"should_only_serve_ads_with_valid_internet_connection", "false"}});

  test::MockIsNetworkConnectionAvailable(ads_client_mock_, false);

  // Act & Assert
  EXPECT_TRUE(HasNetworkConnectionPermission());
}

}  // namespace catsxp_ads
