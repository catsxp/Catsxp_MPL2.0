/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/url_request/subdivision_url_request_json_reader_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_constants.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::json::reader {

TEST(CatsxpAdsSubdivisionUrlRequestJsonReaderUtilTest, ParseJson) {
  // Act & Assert
  EXPECT_EQ("US-CA", ParseSubdivision(
                         R"(
                            {
                              "country": "US",
                              "region": "CA"
                            })"));
}

TEST(CatsxpAdsSubdivisionUrlRequestJsonReaderUtilTest, DoNotParseMalformedJson) {
  // Act & Assert
  EXPECT_FALSE(ParseSubdivision(test::kMalformedJson));
}

TEST(CatsxpAdsSubdivisionUrlRequestJsonReaderUtilTest,
     DoNotParseIfMissingCountry) {
  // Act & Assert
  EXPECT_FALSE(ParseSubdivision(
      R"(
          {
            "region": "CA"
          })"));
}

TEST(CatsxpAdsSubdivisionUrlRequestJsonReaderUtilTest,
     DoNotParseifEmptyCountry) {
  // Act & Assert
  EXPECT_FALSE(ParseSubdivision(
      R"(
          {
            "country": "",
            "region": "CA"
          })"));
}

TEST(CatsxpAdsSubdivisionUrlRequestJsonReaderUtilTest,
     DoNotParseIfMissingRegion) {
  // Act & Assert
  EXPECT_FALSE(ParseSubdivision(
      R"(
          {
            "country": "US"
          })"));
}

TEST(CatsxpAdsSubdivisionUrlRequestJsonReaderUtilTest, DoNotParseIfEmptyRegion) {
  // Act & Assert
  EXPECT_FALSE(ParseSubdivision(
      R"(
          {
            "country": "US",
            "region": ""
          })"));
}

}  // namespace catsxp_ads::json::reader
