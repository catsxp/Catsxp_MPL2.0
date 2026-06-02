/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_util.h"

#include <optional>

#include "catsxp/components/catsxp_ads/core/internal/ads_core/ads_core_util.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_info.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_url_request_json_reader.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/test/catalog_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/file_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsSegmentUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsSegmentUtilTest, GetSegmentsFromCatalog) {
  // Arrange
  std::optional<std::string> contents =
      test::MaybeReadFileToStringAndReplaceTags(
          test::kCatalogWithMultipleCampaignsJsonFilename);
  ASSERT_TRUE(contents);

  std::optional<CatalogInfo> catalog = json::reader::ReadCatalog(*contents);
  ASSERT_TRUE(catalog);

  // Act
  const SegmentList segments = GetSegments(*catalog);

  // Assert
  const SegmentList expected_segments = {"technology & computing",
                                         "untargeted"};
  EXPECT_EQ(expected_segments, segments);
}

TEST_F(CatsxpAdsSegmentUtilTest, GetSegmentsFromEmptyCatalog) {
  // Act & Assert
  EXPECT_THAT(GetSegments(/*catalog=*/{}), ::testing::IsEmpty());
}

TEST_F(CatsxpAdsSegmentUtilTest, GetParentSegmentFromParentChildSegment) {
  // Act & Assert
  EXPECT_EQ("technology & computing",
            GetParentSegment("technology & computing-software"));
}

TEST_F(CatsxpAdsSegmentUtilTest, GetParentSegmentFromParentSegment) {
  // Act & Assert
  EXPECT_EQ("technology & computing",
            GetParentSegment("technology & computing"));
}

TEST_F(CatsxpAdsSegmentUtilTest, GetParentSegments) {
  // Arrange
  const SegmentList segments = {"technology & computing-software",
                                "personal finance-personal finance",
                                "automotive"};

  // Act
  const SegmentList parent_segments = GetParentSegments(segments);

  // Assert
  const SegmentList expected_parent_segments = {
      "technology & computing", "personal finance", "automotive"};
  EXPECT_EQ(expected_parent_segments, parent_segments);
}

TEST_F(CatsxpAdsSegmentUtilTest, GetParentSegmentsForEmptyList) {
  // Act & Assert
  EXPECT_THAT(GetParentSegments(/*segments=*/{}), ::testing::IsEmpty());
}

TEST_F(CatsxpAdsSegmentUtilTest, ShouldFilterMatchingParentChildSegment) {
  // Arrange
  GetReactions().SegmentsForTesting() = {
      {"parent-child", mojom::ReactionType::kDisliked}};

  // Act & Assert
  EXPECT_TRUE(ShouldFilterSegment("parent-child"));
}

TEST_F(CatsxpAdsSegmentUtilTest, ShouldNotFilterNonMatchingParentChildSegment) {
  // Arrange
  GetReactions().SegmentsForTesting() = {
      {"parent-child", mojom::ReactionType::kDisliked}};

  // Act & Assert
  EXPECT_FALSE(ShouldFilterSegment("foo-bar"));
}

TEST_F(CatsxpAdsSegmentUtilTest, ShouldFilterMatchingParentSegment) {
  // Arrange
  GetReactions().SegmentsForTesting() = {
      {"parent", mojom::ReactionType::kDisliked}};

  // Act & Assert
  EXPECT_TRUE(ShouldFilterSegment("parent"));
}

TEST_F(CatsxpAdsSegmentUtilTest, ShouldNotFilterNonMatchingParentSegment) {
  // Arrange
  GetReactions().SegmentsForTesting() = {
      {"parent", mojom::ReactionType::kDisliked}};

  // Act & Assert
  EXPECT_FALSE(ShouldFilterSegment("foo"));
}

TEST_F(CatsxpAdsSegmentUtilTest,
       ShouldFilterAgainstParentForMatchingParentSegmentWithChild) {
  // Arrange
  GetReactions().SegmentsForTesting() = {
      {"parent", mojom::ReactionType::kDisliked}};

  // Act & Assert
  EXPECT_TRUE(ShouldFilterSegment("parent-child"));
}

TEST_F(CatsxpAdsSegmentUtilTest,
       ShouldNotFilterAgainstParentForNonMatchingParentSegmentWithChild) {
  // Arrange
  GetReactions().SegmentsForTesting() = {
      {"parent", mojom::ReactionType::kDisliked}};

  // Act & Assert
  EXPECT_FALSE(ShouldFilterSegment("foo-bar"));
}

TEST_F(CatsxpAdsSegmentUtilTest, HasChildSegment) {
  // Act & Assert
  EXPECT_TRUE(HasChildSegment("technology & computing-windows"));
}

TEST_F(CatsxpAdsSegmentUtilTest, DoesNotHaveChildSegment) {
  // Act & Assert
  EXPECT_FALSE(HasChildSegment("technology & computing"));
}

}  // namespace catsxp_ads
