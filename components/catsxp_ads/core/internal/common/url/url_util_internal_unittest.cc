/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/url/url_util_internal.h"

#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::internal {

TEST(CatsxpAdsUrlUtilInternalTest, HasUrlSearchQueryNameAndValue) {
  // Act & Assert
  EXPECT_TRUE(HasSearchQuery(GURL("https://xyzzy.com/?search=thud")));
}

TEST(CatsxpAdsUrlUtilInternalTest, DoesNotHaveUrlSearchQueryName) {
  // Act & Assert
  EXPECT_FALSE(HasSearchQuery(GURL("https://xyzzy.com/?foo=bar")));
}

TEST(CatsxpAdsUrlUtilInternalTest, HasUrlSearchQueryNameAndEmptyValue) {
  // Act & Assert
  EXPECT_FALSE(HasSearchQuery(GURL("https://xyzzy.com/?search=")));
}

TEST(CatsxpAdsUrlUtilInternalTest, HasSearchQueryNameWithNoValue) {
  // Act & Assert
  EXPECT_FALSE(HasSearchQuery(GURL("https://xyzzy.com/?search")));
}

TEST(CatsxpAdsUrlUtilInternalTest, DoesETLDPlusOneContainWildcards) {
  // Act & Assert
  EXPECT_TRUE(DoesETLDPlusOneContainWildcards(GURL("https://*.appspot.com")));
  EXPECT_TRUE(DoesETLDPlusOneContainWildcards(GURL("https://*.com")));
}

TEST(CatsxpAdsUrlUtilInternalTest, DoesETLDPlusOneNotContainWildcards) {
  // Act & Assert
  EXPECT_FALSE(DoesETLDPlusOneContainWildcards(GURL("https://*.xyzzy.com")));
  EXPECT_FALSE(
      DoesETLDPlusOneContainWildcards(GURL("https://*.r.appspot.com")));
}

TEST(CatsxpAdsUrlUtilInternalTest, HostHasRegistryControlledDomain) {
  // Act & Assert
  EXPECT_TRUE(HostHasRegistryControlledDomain("mysite.appspot.com"));
  EXPECT_TRUE(HostHasRegistryControlledDomain("https://www.google.co.uk"));
  EXPECT_TRUE(HostHasRegistryControlledDomain("https://google.co.uk"));
  EXPECT_TRUE(HostHasRegistryControlledDomain("https://foo.aeroclub.aero"));
  EXPECT_TRUE(
      HostHasRegistryControlledDomain("https://example.mysite.appspot.com"));
}

TEST(CatsxpAdsUrlUtilInternalTest, HostDoesNotHaveRegistryControlledDomain) {
  // Act & Assert
  EXPECT_FALSE(HostHasRegistryControlledDomain("https://hello.unknown"));
}

TEST(CatsxpAdsUrlUtilInternalTest,
     ShouldNotSupportInternalUrlWithChromeSchemeAndFooBarHost) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://foobar")));
}

TEST(CatsxpAdsUrlUtilInternalTest,
     ShouldSupportInternalUrlWithChromeSchemeAndGettingStartedHost) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportInternalUrl(GURL("chrome://getting-started")));
}

TEST(CatsxpAdsUrlUtilInternalTest,
     ShouldNotSupportInternalUrlWithChromeSchemeAndGettingStartedHostAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://getting-started/foo")));
}

TEST(CatsxpAdsUrlUtilInternalTest,
     ShouldSupportInternalUrlWithChromeSchemeAndWalletHost) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportInternalUrl(GURL("chrome://wallet")));
}

TEST(CatsxpAdsUrlUtilInternalTest,
     ShouldNotSupportInternalUrlWithChromeSchemeAndWalletHostAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://wallet/foo")));
}

TEST(CatsxpAdsUrlUtilInternalTest,
     ShouldNotSupportInternalUrlWithChromeSchemeAndWalletHostAndQuery) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://wallet?x=test")));
}

TEST(CatsxpAdsUrlUtilInternalTest,
     ShouldSupportInternalUrlWithChromeSchemeAndSyncHost) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportInternalUrl(GURL("chrome://sync")));
}

TEST(CatsxpAdsUrlUtilInternalTest,
     ShouldNotSupportInternalUrlWithChromeSchemeAndSyncHostAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://sync/foo")));
}

TEST(CatsxpAdsUrlUtilInternalTest,
     ShouldSupportInternalUrlWithChromeSchemeAndLeoAiHost) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportInternalUrl(GURL("chrome://leo-ai")));
}

TEST(CatsxpAdsUrlUtilInternalTest,
     ShouldNotSupportInternalUrlWithChromeSchemeAndLeoAiHostAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://leo-ai/foo")));
}

TEST(CatsxpAdsUrlUtilInternalTest,
     ShouldSupportInternalUrlWithChromeSchemeAndRewardsHost) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportInternalUrl(GURL("chrome://rewards")));
}

TEST(CatsxpAdsUrlUtilInternalTest,
     ShouldNotSupportInternalUrlWithChromeSchemeAndRewardsHostAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://rewards/foo")));
}

TEST(CatsxpAdsUrlUtilInternalTest,
     ShouldNotSupportInternalUrlWithChromeSchemeAndSettingsHost) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://settings")));
}

TEST(CatsxpAdsUrlUtilInternalTest,
     ShouldNotSupportInternalUrlWithChromeSchemeAndSettingsHostAndFooBarPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://settings/foobar")));
}

TEST(
    CatsxpAdsUrlUtilInternalTest,
    ShouldSupportInternalUrlWithChromeSchemeAndSettingsHostAndSurveyPanelistPath) {
  // Act & Assert
  EXPECT_TRUE(
      ShouldSupportInternalUrl(GURL("chrome://settings/surveyPanelist")));
}

TEST(
    CatsxpAdsUrlUtilInternalTest,
    ShouldSupportInternalUrlWithChromeSchemeAndSettingsHostAndSearchEnginesPath) {
  // Act & Assert
  EXPECT_TRUE(
      ShouldSupportInternalUrl(GURL("chrome://settings/searchEngines")));
}

TEST(
    CatsxpAdsUrlUtilInternalTest,
    ShouldSupportInternalUrlWithChromeSchemeAndSettingsHostAndSearchEnginesDefaultSearchPath) {
  // Act & Assert
  EXPECT_TRUE(
      ShouldSupportInternalUrl(GURL("chrome://settings/search/defaultSearch")));
}

TEST(
    CatsxpAdsUrlUtilInternalTest,
    ShouldSupportInternalUrlWithChromeSchemeAndSettingsHostSearchEnginesPathAndSearchQuery) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportInternalUrl(
      GURL("chrome://settings/searchEngines?search=foobar")));
}

TEST(
    CatsxpAdsUrlUtilInternalTest,
    ShouldNotSupportInternalUrlWithChromeSchemeAndSettingsHostSearchEnginesPathAndMultipleSearchQueries) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(
      GURL("chrome://settings/searchEngines?search=foo&bar=baz")));
}

TEST(
    CatsxpAdsUrlUtilInternalTest,
    ShouldNotSupportInternalUrlWithChromeSchemeAndSettingsHostSearchEnginesPathAndInvalidQuery) {
  // Act & Assert
  EXPECT_FALSE(
      ShouldSupportInternalUrl(GURL("chrome://settings/searchEngines?search")));
}

TEST(CatsxpAdsUrlUtilInternalTest,
     ShouldSupportInternalUrlWithChromeSchemeAndSettingsHostAndSearchPath) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportInternalUrl(GURL("chrome://settings/search")));
}

TEST(
    CatsxpAdsUrlUtilInternalTest,
    ShouldSupportInternalUrlWithChromeSchemeAndSettingsHostSearchPathAndSearchQuery) {
  // Act & Assert
  EXPECT_TRUE(
      ShouldSupportInternalUrl(GURL("chrome://settings/search?search=foobar")));
}

TEST(
    CatsxpAdsUrlUtilInternalTest,
    ShouldNotSupportInternalUrlWithChromeSchemeAndSettingsHostSearchPathAndMultipleSearchQueries) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(
      GURL("chrome://settings/search?search=foo&bar=baz")));
}

TEST(
    CatsxpAdsUrlUtilInternalTest,
    ShouldNotSupportInternalUrlWithChromeSchemeAndSettingsHostSearchPathAndInvalidQuery) {
  // Act & Assert
  EXPECT_FALSE(
      ShouldSupportInternalUrl(GURL("chrome://settings/search?search")));
}

TEST(CatsxpAdsUrlUtilInternalTest,
     ShouldNotSupportInternalUrlWithChromeSchemeAndSettingsHostAndQuery) {
  // Act & Assert
  EXPECT_FALSE(
      ShouldSupportInternalUrl(GURL("chrome://settings/?search=foobar")));
}

TEST(
    CatsxpAdsUrlUtilInternalTest,
    ShouldNotSupportInternalUrlWithChromeSchemeAndSettingsHostAndInvalidQuery) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://settings/?search")));
}

TEST(CatsxpAdsUrlUtilInternalTest, ShouldNotSupportMalformedUrl) {
  // Act & Assert
  EXPECT_FALSE(
      ShouldSupportInternalUrl(GURL("http://foobar.com/chrome://wallet")));
}

}  // namespace catsxp_ads::internal
