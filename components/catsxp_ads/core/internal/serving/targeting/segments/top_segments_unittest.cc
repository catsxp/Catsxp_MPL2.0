/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/segments/top_segments.h"

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {
constexpr size_t kSegmentsMaxCount = 2;
}  // namespace

class CatsxpAdsTopSegmentsTest : public test::TestBase {};

TEST_F(CatsxpAdsTopSegmentsTest, GetTopChildSegments) {
  // Arrange
  const SegmentList segments = {"parent_1-child", "parent_2-child",
                                "parent_3-child"};

  // Act
  const SegmentList top_segments = GetTopSegments(segments, kSegmentsMaxCount,
                                                  /*parent_only=*/false);

  // Assert
  const SegmentList expected_top_segments = {"parent_1-child",
                                             "parent_2-child"};
  EXPECT_EQ(expected_top_segments, top_segments);
}

TEST_F(CatsxpAdsTopSegmentsTest, GetEmptyTopChildSegments) {
  EXPECT_THAT(GetTopSegments(/*segments=*/{}, kSegmentsMaxCount,
                             /*parent_only=*/false),
              ::testing::IsEmpty());
}

TEST_F(CatsxpAdsTopSegmentsTest, GetTopParentSegments) {
  // Arrange
  const SegmentList segments = {"parent_1-child", "parent_2-child",
                                "parent_3-child"};

  // Act
  const SegmentList top_segments = GetTopSegments(segments, kSegmentsMaxCount,
                                                  /*parent_only=*/true);

  // Assert
  const SegmentList expected_top_segments = {"parent_1", "parent_2"};
  EXPECT_EQ(expected_top_segments, top_segments);
}

TEST_F(CatsxpAdsTopSegmentsTest, GetEmptyTopParentSegments) {
  EXPECT_THAT(GetTopSegments(/*segments=*/{}, kSegmentsMaxCount,
                             /*parent_only=*/false),
              ::testing::IsEmpty());
}

}  // namespace catsxp_ads
