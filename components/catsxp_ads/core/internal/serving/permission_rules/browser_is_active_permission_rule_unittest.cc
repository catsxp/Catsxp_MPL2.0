/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/browser_is_active_permission_rule.h"

#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/permission_rule_feature.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsBrowserIsActivePermissionRuleTest : public test::TestBase {};

TEST_F(CatsxpAdsBrowserIsActivePermissionRuleTest, ShouldAllow) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  ads_client_notifier_.NotifyBrowserDidBecomeActive();
  ads_client_notifier_.NotifyBrowserDidEnterForeground();

  // Act & Assert
  EXPECT_TRUE(HasBrowserIsActivePermission());
}

TEST_F(CatsxpAdsBrowserIsActivePermissionRuleTest, ShouldNotAllow) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  ads_client_notifier_.NotifyBrowserDidResignActive();
  ads_client_notifier_.NotifyBrowserDidEnterBackground();

  // Act & Assert
  EXPECT_FALSE(HasBrowserIsActivePermission());
}

TEST_F(CatsxpAdsBrowserIsActivePermissionRuleTest,
       ShouldAllowIfPermissionRuleIsDisabled) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kPermissionRulesFeature,
      {{"should_only_serve_ads_if_browser_is_active", "false"}});

  ads_client_notifier_.NotifyBrowserDidResignActive();
  ads_client_notifier_.NotifyBrowserDidEnterBackground();

  // Act & Assert
  EXPECT_TRUE(HasBrowserIsActivePermission());
}

TEST_F(CatsxpAdsBrowserIsActivePermissionRuleTest,
       ShouldNotAllowIfWindowIsActiveAndBrowserIsBackgrounded) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  ads_client_notifier_.NotifyBrowserDidBecomeActive();
  ads_client_notifier_.NotifyBrowserDidEnterBackground();

  // Act & Assert
  EXPECT_FALSE(HasBrowserIsActivePermission());
}

TEST_F(CatsxpAdsBrowserIsActivePermissionRuleTest,
       ShouldNotAllowIfWindowIsInactiveAndBrowserIsForegrounded) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  ads_client_notifier_.NotifyBrowserDidResignActive();
  ads_client_notifier_.NotifyBrowserDidEnterForeground();

  // Act & Assert
  EXPECT_FALSE(HasBrowserIsActivePermission());
}

TEST_F(CatsxpAdsBrowserIsActivePermissionRuleTest,
       ShouldNotAllowIfWindowIsInactiveAndBrowserIsBackgrounded) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  ads_client_notifier_.NotifyBrowserDidResignActive();
  ads_client_notifier_.NotifyBrowserDidEnterBackground();

  // Act & Assert
  EXPECT_FALSE(HasBrowserIsActivePermission());
}

}  // namespace catsxp_ads
