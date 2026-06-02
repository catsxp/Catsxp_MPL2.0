/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/algorithm/count_if_until_util.h"

#include <cstddef>
#include <vector>

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsCountIfUntilUtilTest,
     CountIfUntilWithEmptyContainerAndStopPredicate) {
  // Arrange
  const std::vector<int> container;
  const auto predicate = [](int number) { return number % 2 == 0; };
  const auto stop_predicate = [](size_t count) { return count == 3; };

  // Act & Assert
  EXPECT_EQ(0U, count_if_until(container, predicate, stop_predicate));
}

TEST(CatsxpAdsCountIfUntilUtilTest, CountIfUntilWithStopPredicate) {
  // Arrange
  const std::vector<int> container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  const auto predicate = [](int number) { return number % 2 == 0; };
  const auto stop_predicate = [](size_t count) { return count == 3; };

  // Act & Assert
  EXPECT_EQ(3U, count_if_until(container, predicate, stop_predicate));
}

TEST(CatsxpAdsCountIfUntilUtilTest, CountIfUntilWithEmptyContainerAndStopCount) {
  // Arrange
  const std::vector<int> container;
  const auto predicate = [](int number) { return number % 2 == 0; };
  const size_t stop_count{0};

  // Act & Assert
  EXPECT_EQ(0U, count_if_until(container, predicate, stop_count));
}

TEST(CatsxpAdsCountIfUntilUtilTest, CountIfUntilWithStopCount) {
  // Arrange
  const std::vector<int> container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  const auto predicate = [](int number) { return number % 2 == 0; };
  const size_t stop_count{3};

  // Act & Assert
  EXPECT_EQ(3U, count_if_until(container, predicate, stop_count));
}

}  // namespace catsxp_ads
