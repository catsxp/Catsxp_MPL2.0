/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/common/url/url_util.h"

#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsUrlUtilTest, GetUrlExcludingQuery) {
  // Act & Assert
  EXPECT_EQ(GURL("https://foo.com/bar"),
            GetUrlExcludingQuery(GURL("https://foo.com/bar?baz=qux")));
}

TEST(CatsxpAdsUrlUtilTest, GetUrlExcludingQueryWhenNoQueryNameAndValue) {
  // Act & Assert
  EXPECT_EQ(GURL("https://foo.com/bar"),
            GetUrlExcludingQuery(GURL("https://foo.com/bar?")));
}

TEST(CatsxpAdsUrlUtilTest, GetUrlExcludingQueryWhenNoQuery) {
  // Act & Assert
  EXPECT_EQ(GURL("https://foo.com/bar"),
            GetUrlExcludingQuery(GURL("https://foo.com/bar")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldNotSupportInvalidUrl) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("some random string")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("//*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("://*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("*://*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("*****")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://?.com")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://?.google.com")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldNotSupportUrlWithNonHttpsScheme) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("*://www.example.com/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("http://www.example.com/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("ftp://www.example.com/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL(
      "ipfs://bafybeigi77rim3p5tw3upw2ca4ep5ng7uaarvrz46zidd2ai6cjh46yxoy/")));
  EXPECT_FALSE(ShouldSupportUrl(GURL(
      "ipfs://bafybeigi77rim3p5tw3upw2ca4ep5ng7uaarvrz46zidd2ai6cjh46yxoy/")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("javascript:alert(1)")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("data:text/html,<h1>hello</h1>")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldNotSupportUrlWithPortNumber) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://www.catsxp.com:1234/thank-you*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://www.catsxp.com:1234*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://catsxp.com:*/x")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://catsxp.com:*")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldNotSupportIpAddress) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://1.2.3.4/thank-you*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://192.168.0.0/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://192.*.*.*/x")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://[::1]/thankyou")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://030000001017/")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://0xc000020f/")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldNotSupportUrlWithUsernameOrPassword) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://user:pwd@catsxp.com/thank-you*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://user@catsxp.com:1234*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://*@catsxp.com/x")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://user:*@catsxp.com/y")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldNotSupportUrlWithWildcardInEtldPlus1) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://www.google.co.*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://www.google.*.uk")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://www.*.co.uk")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://www.google.co.uk*")));
  EXPECT_FALSE(
      ShouldSupportUrl(GURL("https://www.comparecredit.com*/secure*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://www.sophos.com*thank-you*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://*.security/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://*.appspot.com/*")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldNotSupportLocalUrl) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://localhost/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://example.local/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://*.example.local/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://*.local/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://localhost*/")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldSupportUrl) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://*.google.co.uk")));
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://www.google.co.uk/*")));
  EXPECT_TRUE(
      ShouldSupportUrl(GURL("https://dashboard.0x.org/create-account/"
                            "verification-sent?tx-relay-catsxp*")));
  EXPECT_TRUE(
      ShouldSupportUrl(GURL("https://www.app.apxlending.com/verify_email*")));
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://bonkmark.com/*/#send")));
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://account.catsxp.com/account/*")));
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://www.cube.exchange/*step=5*")));
  EXPECT_TRUE(ShouldSupportUrl(GURL(
      "https://play.google.com/store/apps/details?id=com.musclewiki.macro*")));
  EXPECT_TRUE(ShouldSupportUrl(
      GURL("https://mail.proton.me/u/*/inbox?welcome=true&ref=*")));
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://sheets.new/*")));
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://*.hello.security/*")));
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://mysite.appspot.com/*")));
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://my.site.developer.app/*")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldNotSupportCatsxpSchemeWithFooBarHostName) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://foobar")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldSupportCatsxpSchemeWithGettingStartedHostName) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("chrome://getting-started")));
}

TEST(CatsxpAdsUrlUtilTest,
     ShouldNotSupportCatsxpSchemeWithGettingStartedHostNameAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://getting-started/foo")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldSupportCatsxpSchemeWithWalletHostName) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("chrome://wallet")));
}

TEST(CatsxpAdsUrlUtilTest,
     ShouldNotSupportCatsxpSchemeWithWalletHostNameAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://wallet/foo")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldSupportCatsxpSchemeWithSyncHostName) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("chrome://sync")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldNotSupportCatsxpSchemeWithSyncHostNameAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://sync/foo")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldSupportCatsxpSchemeWithRewardsHostName) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("chrome://rewards")));
}

TEST(CatsxpAdsUrlUtilTest,
     ShouldNotSupportCatsxpSchemeWithRewardsHostNameAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://rewards/foo")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldSupportCatsxpSchemeWithLeoAiHostName) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("chrome://leo-ai")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldNotSupportCatsxpSchemeWithLeoAiHostNameAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://leo-ai/foo")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldNotSupportCatsxpSchemeWithSettingsHostName) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://settings")));
}

TEST(CatsxpAdsUrlUtilTest,
     ShouldNotSupportCatsxpSchemeWithSettingsHostNameAndFooBarPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://settings/foobar")));
}

TEST(CatsxpAdsUrlUtilTest,
     ShouldSupportCatsxpSchemeWithSettingsHostNameAndSearchEnginesPath) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("chrome://settings/searchEngines")));
}

TEST(
    CatsxpAdsUrlUtilTest,
    ShouldSupportCatsxpSchemeWithSettingsHostNameSearchEnginesPathAndSearchQuery) {
  // Act & Assert
  EXPECT_TRUE(
      ShouldSupportUrl(GURL("chrome://settings/searchEngines?search=foobar")));
}

TEST(
    CatsxpAdsUrlUtilTest,
    ShouldNotSupportCatsxpSchemeWithSettingsHostNameSearchEnginesPathAndMultipleSearchQueries) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(
      GURL("chrome://settings/searchEngines?search=foo&bar=baz")));
}

TEST(
    CatsxpAdsUrlUtilTest,
    ShouldNotSupportCatsxpSchemeWithSettingsHostNameSearchEnginesPathAndInvalidQuery) {
  // Act & Assert
  EXPECT_FALSE(
      ShouldSupportUrl(GURL("chrome://settings/searchEngines?search")));
}

TEST(CatsxpAdsUrlUtilTest,
     ShouldSupportCatsxpSchemeWithSettingsHostNameAndSearchPath) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("chrome://settings/search")));
}

TEST(CatsxpAdsUrlUtilTest,
     ShouldSupportCatsxpSchemeWithSettingsHostNameSearchPathAndSearchQuery) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("chrome://settings/search?search=foobar")));
}

TEST(
    CatsxpAdsUrlUtilTest,
    ShouldNotSupportCatsxpSchemeWithSettingsHostNameSearchPathAndMultipleSearchQueries) {
  // Act & Assert
  EXPECT_FALSE(
      ShouldSupportUrl(GURL("chrome://settings/search?search=foo&bar=baz")));
}

TEST(CatsxpAdsUrlUtilTest,
     ShouldNotSupportCatsxpSchemeWithSettingsHostNameSearchPathAndInvalidQuery) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://settings/search?search")));
}

TEST(CatsxpAdsUrlUtilTest,
     ShouldNotSupportCatsxpSchemeWithSettingsHostNameAndQuery) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://settings/?search=foobar")));
}

TEST(CatsxpAdsUrlUtilTest,
     ShouldNotSupportCatsxpSchemeWithSettingsHostNameAndInvalidQuery) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://settings/?search")));
}

TEST(CatsxpAdsUrlUtilTest, ShouldNotSupportMalformedUrl) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("http://foobar.com/chrome://wallet")));
}

TEST(CatsxpAdsUrlUtilTest, UrlMatchesPatternWithNoWildcards) {
  // Act & Assert
  EXPECT_TRUE(MatchUrlPattern(GURL("https://www.foo.com/"),
                              /*pattern=*/"https://www.foo.com/"));
}

TEST(CatsxpAdsUrlUtilTest, UrlWithPathMatchesPatternWithNoWildcards) {
  // Act & Assert
  EXPECT_TRUE(MatchUrlPattern(GURL("https://www.foo.com/bar"),
                              /*pattern=*/"https://www.foo.com/bar"));
}

TEST(CatsxpAdsUrlUtilTest, UrlDoesNotMatchPattern) {
  // Act & Assert
  EXPECT_FALSE(
      MatchUrlPattern(GURL("https://www.foo.com/"), /*pattern=*/"www.foo.com"));
}

TEST(CatsxpAdsUrlUtilTest, UrlMatchesPatternWithQuery) {
  // Act & Assert
  EXPECT_TRUE(
      MatchUrlPattern(GURL("https://dashboard.0x.org/create-account/"
                           "verification-sent?tx-relay-catsxp-browser"),
                      /*pattern=*/"https://dashboard.0x.org/create-account/"
                                  "verification-sent?tx-relay-catsxp*"));
}

TEST(CatsxpAdsUrlUtilTest, UrlDoesNotMatchPatternWithQuery) {
  // Act & Assert
  EXPECT_FALSE(
      MatchUrlPattern(GURL("https://dashboard.0x.org/create-account/"
                           "verification-sent-tx-relay-catsxp-browser"),
                      /*pattern=*/"https://dashboard.0x.org/create-account/"
                                  "verification-sent?tx-relay-catsxp*"));
}

TEST(CatsxpAdsUrlUtilTest, UrlDoesNotMatchPatternWithMissingEmptyPath) {
  // Act & Assert
  EXPECT_FALSE(MatchUrlPattern(GURL("https://www.foo.com/"),
                               /*pattern=*/"https://www.foo.com"));
}

TEST(CatsxpAdsUrlUtilTest, UrlMatchesEndWildcardPattern) {
  // Act & Assert
  EXPECT_TRUE(MatchUrlPattern(GURL("https://www.foo.com/bar?key=test"),
                              /*pattern=*/"https://www.foo.com/bar*"));
}

TEST(CatsxpAdsUrlUtilTest, UrlMatchesMidWildcardPattern) {
  // Act & Assert
  EXPECT_TRUE(MatchUrlPattern(GURL("https://www.foo.com/woo-bar-hoo"),
                              /*pattern=*/"https://www.foo.com/woo*hoo"));
}

TEST(CatsxpAdsUrlUtilTest, UrlDoesNotMatchMidWildcardPattern) {
  // Act & Assert
  EXPECT_FALSE(MatchUrlPattern(GURL("https://www.foo.com/woo"),
                               /*pattern=*/"https://www.foo.com/woo*hoo"));
}

TEST(CatsxpAdsUrlUtilTest, SameDomainOrHost) {
  // Act & Assert
  EXPECT_TRUE(SameDomainOrHost(GURL("https://foo.com?bar=test"),
                               GURL("https://subdomain.foo.com/bar")));
}

TEST(CatsxpAdsUrlUtilTest, NotSameDomainOrHost) {
  // Act & Assert
  EXPECT_FALSE(SameDomainOrHost(GURL("https://foo.com?bar=test"),
                                GURL("https://subdomain.bar.com/foo")));
}

TEST(CatsxpAdsUrlUtilTest, SameDomainOrHostForUrlWithNoSubdomain) {
  // Act & Assert
  EXPECT_TRUE(SameDomainOrHost(GURL("https://foo.com?bar=test"),
                               GURL("https://foo.com/bar")));
}

TEST(CatsxpAdsUrlUtilTest, NotSameDomainOrHostForUrlWithNoSubdomain) {
  // Act & Assert
  EXPECT_FALSE(SameDomainOrHost(GURL("https://foo.com?bar=test"),
                                GURL("https://bar.com/foo")));
}

TEST(CatsxpAdsUrlUtilTest, SameDomainOrHostForUrlWithRef) {
  // Act & Assert
  EXPECT_TRUE(SameDomainOrHost(GURL("https://foo.com?bar=test#ref"),
                               GURL("https://foo.com/bar")));
}

TEST(CatsxpAdsUrlUtilTest, NotSameDomainOrHostForUrlWithRef) {
  // Act & Assert
  EXPECT_FALSE(SameDomainOrHost(GURL("https://foo.com?bar=test#ref"),
                                GURL("https://bar.com/foo")));
}

TEST(CatsxpAdsUrlUtilTest, DomainOrHostExists) {
  // Arrange
  const std::vector<GURL> urls = {GURL("https://foo.com"),
                                  GURL("https://bar.com")};

  // Act & Assert
  EXPECT_TRUE(DomainOrHostExists(urls, GURL("https://bar.com/foo")));
}

TEST(CatsxpAdsUrlUtilTest, DomainOrHostDoesNotExist) {
  // Arrange
  const std::vector<GURL> urls = {GURL("https://foo.com"),
                                  GURL("https://bar.com")};

  // Act & Assert
  EXPECT_FALSE(DomainOrHostExists(urls, GURL("https://baz.com/qux")));
}

}  // namespace catsxp_ads
