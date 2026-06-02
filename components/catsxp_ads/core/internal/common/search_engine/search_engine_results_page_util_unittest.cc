/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/search_engine/search_engine_results_page_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/search_engine/test/search_engine_results_page_test_constants.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsSearchEngineResultsPageUtilTest, IsSearchEngineResultsPage) {
  // Act & Assert
  for (const auto& url : test::GetSearchEngineResultsPageUrls()) {
    EXPECT_TRUE(IsSearchEngineResultsPage(url));
  }
}

TEST(CatsxpAdsSearchEngineResultsPageUtilTest, IsNotSearchEngineResultsPage) {
  // Act & Assert
  EXPECT_FALSE(IsSearchEngineResultsPage(GURL("https://catsxp.com/")));
}

TEST(CatsxpAdsSearchEngineResultsPageUtilTest,
     IsNotSearchEngineResultsPageWithInvalidUrl) {
  // Act & Assert
  EXPECT_FALSE(IsSearchEngineResultsPage(GURL("INVALID")));
}

TEST(CatsxpAdsSearchEngineResultsPageUtilTest, ExtractSearchTermQueryValue) {
  // Act & Assert
  for (const auto& url : test::GetSearchEngineResultsPageUrls()) {
    if (std::optional<std::string> search_term_query_value =
            ExtractSearchTermQueryValue(url)) {
      EXPECT_EQ("foobar", search_term_query_value);
    }
  }
}

TEST(CatsxpAdsSearchEngineResultsPageUtilTest,
     FailToExtractSearchTermQueryValueFromUrlWithMissingQuery) {
  // Act & Assert
  EXPECT_FALSE(ExtractSearchTermQueryValue(GURL("https://google.com/")));
}

TEST(CatsxpAdsSearchEngineResultsPageUtilTest,
     FailToExtractSearchTermQueryValueFromInvalidUrl) {
  // Act & Assert
  EXPECT_FALSE(ExtractSearchTermQueryValue(GURL("INVALID")));
}

}  // namespace catsxp_ads
