/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/algorithm/split_vector_util.h"

#include <string>

#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsSplitVectorUtilTest, SplitVectorIntoSingleChunk) {
  // Arrange
  const std::vector<std::string> element = {"item 1", "item 2", "item 3",
                                            "item 4", "item 5", "item 6"};

  // Act
  const std::vector<std::vector<std::string>> elements =
      SplitVector(element, 6);

  // Assert
  EXPECT_THAT(elements, ::testing::SizeIs(1));
}

TEST(CatsxpAdsSplitVectorUtilTest,
     SplitVectorIntoSingleChunkWhenChunkSizeIsLargerThanVectorSize) {
  // Arrange
  const std::vector<std::string> element = {"item 1", "item 2", "item 3",
                                            "item 4", "item 5", "item 6"};

  // Act
  const std::vector<std::vector<std::string>> elements =
      SplitVector(element, 7);

  // Assert
  const std::vector<std::vector<std::string>> expected_elements = {element};
  EXPECT_EQ(expected_elements, elements);
}

TEST(CatsxpAdsSplitVectorUtilTest, SplitVectorIntoMultipleEvenChunks) {
  // Arrange
  const std::vector<std::string> element = {
      "item 1", "item 2", "item 3", "item 4", "item 5", "item 6",
  };

  // Act
  const std::vector<std::vector<std::string>> elements =
      SplitVector(element, 3);

  // Assert
  const std::vector<std::vector<std::string>> expected_elements = {
      {"item 1", "item 2", "item 3"}, {"item 4", "item 5", "item 6"}};
  EXPECT_EQ(expected_elements, elements);
}

TEST(CatsxpAdsSplitVectorUtilTest, SplitVectorIntoMultipleUnevenChunks) {
  // Arrange
  const std::vector<std::string> element = {"item 1", "item 2", "item 3",
                                            "item 4", "item 5"};

  // Act
  const std::vector<std::vector<std::string>> elements =
      SplitVector(element, 3);

  // Assert
  const std::vector<std::vector<std::string>> expected_elements = {
      {"item 1", "item 2", "item 3"}, {"item 4", "item 5"}};
  EXPECT_EQ(expected_elements, elements);
}

TEST(CatsxpAdsSplitVectorUtilTest, SplitEmptyVector) {
  // Arrange
  const std::vector<std::string> element;

  // Act
  const std::vector<std::vector<std::string>> elements =
      SplitVector(element, 5);

  // Assert
  EXPECT_THAT(elements, ::testing::IsEmpty());
}

}  // namespace catsxp_ads
