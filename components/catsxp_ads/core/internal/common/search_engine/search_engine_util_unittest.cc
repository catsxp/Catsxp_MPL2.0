/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/search_engine/search_engine_util.h"

#include <vector>

#include "base/strings/strcat.h"
#include "catsxp/components/catsxp_ads/core/internal/common/search_engine/search_engine_domain_extension_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/search_engine/search_engine_subdomain_constants.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsSearchEngineUtilTest, IsMultilingualAmazonSearchEngine) {
  // Act & Assert
  for (const auto& domain_extension : kAmazonSearchEngineDomainExtensions) {
    EXPECT_TRUE(IsSearchEngine(
        GURL(base::StrCat({"https://www.amazon.", domain_extension, "/"}))));
  }
}

TEST(CatsxpAdsSearchEngineUtilTest, IsNotMultilingualAmazonSearchEngine) {
  // Act & Assert
  EXPECT_FALSE(IsSearchEngine(GURL("https://www.amazon.foobar/")));
}

TEST(CatsxpAdsSearchEngineUtilTest, IsMultilingualGoogleSearchEngine) {
  // Act & Assert
  for (const auto& domain_extension : kGoogleSearchEngineDomainExtensions) {
    EXPECT_TRUE(IsSearchEngine(
        GURL(base::StrCat({"https://www.google.", domain_extension, "/"}))));
  }
}

TEST(CatsxpAdsSearchEngineUtilTest, IsNotMultilingualGoogleSearchEngine) {
  // Act & Assert
  EXPECT_FALSE(IsSearchEngine(GURL("https://www.google.foobar/")));
}

TEST(CatsxpAdsSearchEngineUtilTest, IsMultilingualMojeekSearchEngine) {
  // Act & Assert
  for (const auto& domain_extension : kMojeekSearchEngineDomainExtensions) {
    EXPECT_TRUE(IsSearchEngine(
        GURL(base::StrCat({"https://www.mojeek.", domain_extension, "/"}))));
  }
}

TEST(CatsxpAdsSearchEngineUtilTest, IsNotMultilingualMojeekSearchEngine) {
  // Act & Assert
  EXPECT_FALSE(IsSearchEngine(GURL("https://www.mojeek.foobar/")));
}

TEST(CatsxpAdsSearchEngineUtilTest, IsMultilingualWikipediaSearchEngine) {
  // Act & Assert
  for (const auto& subdomain : kWikipediaSearchEngineSubdomains) {
    EXPECT_TRUE(IsSearchEngine(
        GURL(base::StrCat({"https://", subdomain, ".wikipedia.org/"}))));
  }
}

TEST(CatsxpAdsSearchEngineUtilTest, IsNotMultilingualWikipediaSearchEngine) {
  // Act & Assert
  EXPECT_FALSE(IsSearchEngine(GURL("https://foobar.wikipedia.org/")));
}

TEST(CatsxpAdsSearchEngineUtilTest, IsMultilingualYahooSearchEngine) {
  // Act & Assert
  for (const auto& subdomain : kYahooSearchEngineSubdomains) {
    EXPECT_TRUE(IsSearchEngine(
        GURL(base::StrCat({"https://", subdomain, ".search.yahoo.com/"}))));
  }
}

TEST(CatsxpAdsSearchEngineUtilTest, IsNotMultilingualYahooSearchEngine) {
  // Act & Assert
  EXPECT_FALSE(IsSearchEngine(GURL("https://foobar.search.yahoo.com/")));
}

TEST(CatsxpAdsSearchEngineUtilTest, IsMonolingualSearchEngine) {
  // Arrange
  const std::vector<GURL> urls = {GURL("https://developer.mozilla.org/en-US/"),
                                  GURL("https://duckduckgo.com/"),
                                  GURL("https://fireball.de/"),
                                  GURL("https://github.com/"),
                                  GURL("https://infogalactic.com/"),
                                  GURL("https://search.catsxp.com/"),
                                  GURL("https://search.yahoo.com/"),
                                  GURL("https://stackoverflow.com/"),
                                  GURL("https://swisscows.com/"),
                                  GURL("https://twitter.com/explore/"),
                                  GURL("https://www.baidu.com/"),
                                  GURL("https://www.bing.com/"),
                                  GURL("https://www.dogpile.com/"),
                                  GURL("https://www.ecosia.org/"),
                                  GURL("https://www.excite.com/"),
                                  GURL("https://www.findx.com/"),
                                  GURL("https://www.gigablast.com/"),
                                  GURL("https://www.lycos.com/"),
                                  GURL("https://www.metacrawler.com/"),
                                  GURL("https://www.petalsearch.com/"),
                                  GURL("https://www.qwant.com/"),
                                  GURL("https://www.semanticscholar.org/"),
                                  GURL("https://www.sogou.com/"),
                                  GURL("https://www.startpage.com/"),
                                  GURL("https://www.webcrawler.com/"),
                                  GURL("https://www.wolframalpha.com/"),
                                  GURL("https://www.youtube.com/"),
                                  GURL("https://yandex.com/")};

  // Act & Assert
  for (const auto& url : urls) {
    EXPECT_TRUE(IsSearchEngine(url));
  }
}

TEST(CatsxpAdsSearchEngineUtilTest, IsNotSearchEngine) {
  // Act & Assert
  EXPECT_FALSE(IsSearchEngine(GURL("https://foobar.com/")));
}

TEST(CatsxpAdsSearchEngineUtilTest, IsNotSearchEngineWithInvalidUrl) {
  // Act & Assert
  EXPECT_FALSE(IsSearchEngine(GURL("INVALID")));
}

}  // namespace catsxp_ads
