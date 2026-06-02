/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_value_util.h"

#include <string_view>

#include "base/test/values_test_util.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

constexpr std::string_view kSegmentsAsJson =
    R"JSON(
        [
          "technology & computing",
          "personal finance-banking",
          "food & drink-restaurants"
        ])JSON";

}  // namespace

TEST(CatsxpAdsSegmentValueUtilTest, SegmentsToList) {
  EXPECT_EQ(
      base::test::ParseJsonList(kSegmentsAsJson),
      SegmentsToList({"technology & computing", "personal finance-banking",
                      "food & drink-restaurants"}));
}

TEST(CatsxpAdsSegmentValueUtilTest, EmptySegmentsToList) {
  EXPECT_THAT(SegmentsToList({}), ::testing::IsEmpty());
}

TEST(CatsxpAdsSegmentValueUtilTest, SegmentsFromList) {
  // Arrange
  const base::ListValue list = base::test::ParseJsonList(kSegmentsAsJson);

  // Act
  const SegmentList segments = SegmentsFromList(list);

  // Assert
  const SegmentList expected_segments = {"technology & computing",
                                         "personal finance-banking",
                                         "food & drink-restaurants"};
  EXPECT_EQ(expected_segments, segments);
}

TEST(CatsxpAdsSegmentValueUtilTest, NoSegmentsFromEmptyList) {
  // Act & Assert
  EXPECT_THAT(SegmentsFromList({}), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
