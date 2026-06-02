/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/full_screen_mode_permission_rule.h"

#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system_types.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/mock_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/permission_rule_feature.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsFullScreenModePermissionRuleTest : public test::TestBase {};

TEST_F(CatsxpAdsFullScreenModePermissionRuleTest, ShouldAllow) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  EXPECT_TRUE(HasFullScreenModePermission());
}

TEST_F(CatsxpAdsFullScreenModePermissionRuleTest, ShouldAlwaysAllowOnAndroid) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  fake_operating_system_.SetType(OperatingSystemType::kAndroid);

  test::MockIsBrowserInFullScreenMode(ads_client_mock_, true);

  // Act & Assert
  EXPECT_TRUE(HasFullScreenModePermission());
}

TEST_F(CatsxpAdsFullScreenModePermissionRuleTest, ShouldAlwaysAllowOnIOS) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  fake_operating_system_.SetType(OperatingSystemType::kIOS);

  test::MockIsBrowserInFullScreenMode(ads_client_mock_, true);

  // Act & Assert
  EXPECT_TRUE(HasFullScreenModePermission());
}

TEST_F(CatsxpAdsFullScreenModePermissionRuleTest, ShouldNotAllow) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  test::MockIsBrowserInFullScreenMode(ads_client_mock_, true);

  // Act & Assert
  EXPECT_FALSE(HasFullScreenModePermission());
}

TEST_F(CatsxpAdsFullScreenModePermissionRuleTest,
       ShouldAllowIfPermissionRuleIsDisabled) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kPermissionRulesFeature,
      {{"should_only_serve_ads_in_windowed_mode", "false"}});

  test::MockIsBrowserInFullScreenMode(ads_client_mock_, true);

  // Act & Assert
  EXPECT_TRUE(HasFullScreenModePermission());
}

}  // namespace catsxp_ads
