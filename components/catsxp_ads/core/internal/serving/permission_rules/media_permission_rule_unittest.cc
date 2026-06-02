/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/media_permission_rule.h"

#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/permission_rule_feature.h"
#include "net/http/http_status_code.h"
#include "url/gurl.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsMediaPermissionRuleTest : public test::TestBase {};

TEST_F(CatsxpAdsMediaPermissionRuleTest, ShouldAllowIfMediaIsNotPlaying) {
  // Act & Assert
  EXPECT_TRUE(HasMediaPermission());
}

TEST_F(CatsxpAdsMediaPermissionRuleTest,
       ShouldAllowIfMediaIsStoppedForSingleTab) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);

  ads_client_notifier_.NotifyTabDidStartPlayingMedia(/*tab_id=*/1);

  ads_client_notifier_.NotifyTabDidStopPlayingMedia(/*tab_id=*/1);

  // Act & Assert
  EXPECT_TRUE(HasMediaPermission());
}

TEST_F(CatsxpAdsMediaPermissionRuleTest,
       ShouldAllowIfMediaIsStoppedOnMultipleTabs) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);

  ads_client_notifier_.NotifyTabDidStartPlayingMedia(/*tab_id=*/1);
  ads_client_notifier_.NotifyTabDidStartPlayingMedia(/*tab_id=*/2);

  ads_client_notifier_.NotifyTabDidStopPlayingMedia(/*tab_id=*/1);
  ads_client_notifier_.NotifyTabDidStopPlayingMedia(/*tab_id=*/2);

  // Act & Assert
  EXPECT_TRUE(HasMediaPermission());
}

TEST_F(CatsxpAdsMediaPermissionRuleTest,
       ShouldAllowIfMediaIsPlayingOnMultipleTabsButStoppedForVisibleTab) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);

  ads_client_notifier_.NotifyTabDidStartPlayingMedia(/*tab_id=*/1);
  ads_client_notifier_.NotifyTabDidStartPlayingMedia(/*tab_id=*/2);

  ads_client_notifier_.NotifyTabDidStopPlayingMedia(/*tab_id=*/1);

  // Act & Assert
  EXPECT_TRUE(HasMediaPermission());
}

TEST_F(CatsxpAdsMediaPermissionRuleTest,
       ShouldNotAllowIfMediaIsPlayingOnVisibleTab) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);

  ads_client_notifier_.NotifyTabDidStartPlayingMedia(/*tab_id=*/1);

  // Act & Assert
  EXPECT_FALSE(HasMediaPermission());
}

TEST_F(
    CatsxpAdsMediaPermissionRuleTest,
    ShouldAlwaysAllowIfMediaIsPlayingOnVisibleTabIfPermissionRuleIsDisabled) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kPermissionRulesFeature,
      {{"should_only_serve_ads_if_media_is_not_playing", "false"}});

  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);

  ads_client_notifier_.NotifyTabDidStartPlayingMedia(/*tab_id=*/1);

  // Act & Assert
  EXPECT_TRUE(HasMediaPermission());
}

TEST_F(CatsxpAdsMediaPermissionRuleTest,
       ShouldNotAllowIfMediaIsPlayingOnMultipleTabs) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);

  ads_client_notifier_.NotifyTabDidStartPlayingMedia(/*tab_id=*/1);
  ads_client_notifier_.NotifyTabDidStartPlayingMedia(/*tab_id=*/2);

  // Act & Assert
  EXPECT_FALSE(HasMediaPermission());
}

TEST_F(CatsxpAdsMediaPermissionRuleTest,
       ShouldNotAllowIfMediaIsPlayingOnMultipleTabsButStoppedForOccludedTab) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);

  ads_client_notifier_.NotifyTabDidStartPlayingMedia(/*tab_id=*/1);
  ads_client_notifier_.NotifyTabDidStartPlayingMedia(/*tab_id=*/2);

  ads_client_notifier_.NotifyTabDidStopPlayingMedia(/*tab_id=*/2);

  // Act & Assert
  EXPECT_FALSE(HasMediaPermission());
}

}  // namespace catsxp_ads
