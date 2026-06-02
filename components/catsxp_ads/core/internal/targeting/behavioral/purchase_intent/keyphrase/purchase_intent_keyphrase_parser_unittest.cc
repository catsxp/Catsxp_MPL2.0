/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/keyphrase/purchase_intent_keyphrase_parser.h"

#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsPurchaseIntentKeyphraseParserTest, ParseKeyphrase) {
  // Act
  const KeywordList keywords = ParseKeyphrase(R"("Audi RS6" Automobile)");

  // Assert
  const KeywordList expected_keywords = {"audi rs6", "automobile"};
  EXPECT_EQ(expected_keywords, keywords);
}

TEST(CatsxpAdsPurchaseIntentKeyphraseParserTest,
     ParsePurchaseIntentKeyphraseStrippingWhitespace) {
  // Act
  const KeywordList keywords =
      ParseKeyphrase(R"("  Mercedes AMG E63S "  Automobile  )");

  // Assert
  const KeywordList expected_keywords = {"mercedes amg e63s", "automobile"};
  EXPECT_EQ(expected_keywords, keywords);
}

TEST(CatsxpAdsPurchaseIntentKeyphraseParserTest, ParseEmptyKeyphrase) {
  // Act
  const KeywordList keywords = ParseKeyphrase("");

  // Assert
  EXPECT_THAT(keywords, ::testing::IsEmpty());
}

}  // namespace catsxp_ads
