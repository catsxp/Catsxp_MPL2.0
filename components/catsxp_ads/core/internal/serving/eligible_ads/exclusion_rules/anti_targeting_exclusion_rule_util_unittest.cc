/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/anti_targeting_exclusion_rule_util.h"

#include "catsxp/components/catsxp_ads/core/internal/history/test/site_history_test_util.h"
#include "catsxp/components/catsxp_ads/core/public/history/site_history.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsAntiTargetingExclusionRuleUtilTest, HasVisitedAntiTargetedSites) {
  // Arrange
  const SiteHistoryList site_history = test::BuildSiteHistory();

  const AntiTargetingSiteList anti_targeting_sites = {
      GURL("https://www.foo.com"), GURL("https://www.bar.com")};

  // Act & Assert
  EXPECT_TRUE(HasVisitedAntiTargetedSites(site_history, anti_targeting_sites));
}

TEST(CatsxpAdsAntiTargetingExclusionRuleUtilTest,
     HasVisitedCaseInsensitiveAntiTargetedSites) {
  // Arrange
  const SiteHistoryList site_history = test::BuildSiteHistory();

  const AntiTargetingSiteList anti_targeting_sites = {
      GURL("HTTPS://WWW.FOO.COM"), GURL("HTTPS://WWW.BAR.COM")};

  // Act & Assert
  EXPECT_TRUE(HasVisitedAntiTargetedSites(site_history, anti_targeting_sites));
}

TEST(CatsxpAdsAntiTargetingExclusionRuleUtilTest,
     HasNotVisitedAntiTargetedSites) {
  // Arrange
  const SiteHistoryList site_history = test::BuildSiteHistory();

  const AntiTargetingSiteList anti_targeting_sites = {
      GURL("https://www.catsxp.com"),
      GURL("https://www.basicattentiontoken.org")};

  // Act & Assert
  EXPECT_FALSE(HasVisitedAntiTargetedSites(site_history, anti_targeting_sites));
}

TEST(CatsxpAdsAntiTargetingExclusionRuleUtilTest,
     HasNotVisitedAntiTargetedInvalidSites) {
  // Arrange
  const SiteHistoryList site_history = test::BuildSiteHistory();

  const AntiTargetingSiteList anti_targeting_sites = {GURL("INVALID")};

  // Act & Assert
  EXPECT_FALSE(HasVisitedAntiTargetedSites(site_history, anti_targeting_sites));
}

TEST(CatsxpAdsAntiTargetingExclusionRuleUtilTest, HasNotVisitedIfNoSiteHistory) {
  // Arrange
  const AntiTargetingSiteList anti_targeting_sites = {GURL("INVALID")};

  // Act & Assert
  EXPECT_FALSE(
      HasVisitedAntiTargetedSites(/*site_history=*/{}, anti_targeting_sites));
}

TEST(CatsxpAdsAntiTargetingExclusionRuleUtilTest,
     HasNotVisitedIfNoAntiTargetedSites) {
  // Arrange
  const SiteHistoryList site_history = test::BuildSiteHistory();

  // Act & Assert
  EXPECT_FALSE(HasVisitedAntiTargetedSites(site_history, /*sites=*/{}));
}

TEST(CatsxpAdsAntiTargetingExclusionRuleUtilTest,
     HasNotVisitedIfNoSiteHistoryAndAntiTargetedSites) {
  // Act & Assert
  EXPECT_FALSE(HasVisitedAntiTargetedSites(/*site_history=*/{}, /*sites=*/{}));
}

}  // namespace catsxp_ads
