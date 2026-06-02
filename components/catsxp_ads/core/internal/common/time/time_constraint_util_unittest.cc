/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/time/time_constraint_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsTimeConstraintUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsTimeConstraintUtilTest, DoesRespectIfNoHistory) {
  // Arrange
  const std::vector<base::Time> history;

  // Act & Assert
  EXPECT_TRUE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/1));
}

TEST_F(CatsxpAdsTimeConstraintUtilTest, DoNotRespectTimeConstraintIfCapIsZero) {
  // Arrange
  const std::vector<base::Time> history;

  // Act & Assert
  EXPECT_TRUE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/0));
}

TEST_F(CatsxpAdsTimeConstraintUtilTest,
       DoesRespectTimeConstraintIfNotExceededCap) {
  // Arrange
  std::vector<base::Time> history;
  history.push_back(test::Now());

  // Act & Assert
  EXPECT_TRUE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/2));
}

TEST_F(CatsxpAdsTimeConstraintUtilTest,
       DoesNotRespectTimeConstraintIfExceededCap) {
  // Arrange
  std::vector<base::Time> history;
  history.push_back(test::Now());
  history.push_back(test::Now());

  // Act & Assert
  EXPECT_FALSE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/2));
}

TEST_F(CatsxpAdsTimeConstraintUtilTest,
       DoesRespectTimeConstraintIfTimeConstraintHasPassed) {
  // Arrange
  std::vector<base::Time> history;
  history.push_back(test::Now());

  AdvanceClockBy(base::Days(1));

  // Act & Assert
  EXPECT_TRUE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/1));
}

TEST_F(CatsxpAdsTimeConstraintUtilTest,
       DoesRespectTimeConstraintOnCuspIfNotExceededCap) {
  // Arrange
  std::vector<base::Time> history;
  history.push_back(test::Now());

  AdvanceClockBy(base::Days(1) - base::Milliseconds(1));

  // Act & Assert
  EXPECT_TRUE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/2));
}

TEST_F(CatsxpAdsTimeConstraintUtilTest,
       DoesNotRespectTimeConstraintOnCuspIfExceededCap) {
  // Arrange
  std::vector<base::Time> history;
  history.push_back(test::Now());

  AdvanceClockBy(base::Days(1) - base::Milliseconds(1));

  // Act & Assert
  EXPECT_FALSE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/1));
}

TEST_F(
    CatsxpAdsTimeConstraintUtilTest,
    DoesRespectTimeConstraintIfHistorySizeIsHigherThanRemainingCapAndTimeConstraintHasPassed) {
  // Arrange
  std::vector<base::Time> history;
  history.push_back(test::Now());
  history.push_back(test::Now());

  AdvanceClockBy(base::Days(1));

  // Act & Assert
  EXPECT_TRUE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/1));
}

TEST_F(CatsxpAdsTimeConstraintUtilTest,
       DoesNotRespectTimeConstraintIfHistorySizeIsHigherThanRemainingCap) {
  // Arrange
  std::vector<base::Time> history;
  history.push_back(test::Now());
  history.push_back(test::Now());

  // Act & Assert
  EXPECT_FALSE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/1));
}

}  // namespace catsxp_ads
