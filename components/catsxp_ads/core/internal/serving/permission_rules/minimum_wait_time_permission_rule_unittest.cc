/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/minimum_wait_time_permission_rule.h"

#include <vector>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsMinimumWaitTimePermissionRuleTest : public test::TestBase {};

TEST_F(CatsxpAdsMinimumWaitTimePermissionRuleTest, ShouldAllowIfNoHistory) {
  // Arrange
  const std::vector<base::Time> history;

  // Act & Assert
  EXPECT_TRUE(HasMinimumWaitTimePermission(
      history, /*time_constraint=*/base::Minutes(1)));
}

TEST_F(CatsxpAdsMinimumWaitTimePermissionRuleTest,
       ShouldAllowIfDoesNotExceedCap) {
  // Arrange
  const std::vector<base::Time> history = {test::Now()};

  AdvanceClockBy(base::Minutes(1));

  // Act & Assert
  EXPECT_TRUE(HasMinimumWaitTimePermission(
      history, /*time_constraint=*/base::Minutes(1)));
}

TEST_F(CatsxpAdsMinimumWaitTimePermissionRuleTest, ShouldNotAllowIfExceedsCap) {
  // Arrange
  const std::vector<base::Time> history = {test::Now()};

  AdvanceClockBy(base::Minutes(1) - base::Milliseconds(1));

  // Act & Assert
  EXPECT_FALSE(HasMinimumWaitTimePermission(
      history, /*time_constraint=*/base::Minutes(1)));
}

}  // namespace catsxp_ads
