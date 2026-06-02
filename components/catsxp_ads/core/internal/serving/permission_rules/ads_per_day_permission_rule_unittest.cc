/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/ads_per_day_permission_rule.h"

#include <vector>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsAdsPerDayPermissionRuleTest : public test::TestBase {};

TEST_F(CatsxpAdsAdsPerDayPermissionRuleTest, ShouldAllowIfNoHistory) {
  // Arrange
  const std::vector<base::Time> history;

  // Act & Assert
  EXPECT_TRUE(HasAdsPerDayPermission(history, /*cap=*/1));
}

TEST_F(CatsxpAdsAdsPerDayPermissionRuleTest, ShouldAllowIfDoesNotExceedCap) {
  // Arrange
  const std::vector<base::Time> history = {test::Now()};

  // Act & Assert
  EXPECT_TRUE(HasAdsPerDayPermission(history, /*cap=*/2));
}

TEST_F(CatsxpAdsAdsPerDayPermissionRuleTest,
       ShouldAllowIfDoesNotExceedCapAfter1Day) {
  // Arrange
  const std::vector<base::Time> history = {test::Now()};

  AdvanceClockBy(base::Days(1));

  // Act & Assert
  EXPECT_TRUE(HasAdsPerDayPermission(history, /*cap=*/1));
}

TEST_F(CatsxpAdsAdsPerDayPermissionRuleTest,
       ShouldNotAllowIfExceedsCapWithin1Day) {
  // Arrange
  const std::vector<base::Time> history = {test::Now()};

  AdvanceClockBy(base::Days(1) - base::Milliseconds(1));

  // Act & Assert
  EXPECT_FALSE(HasAdsPerDayPermission(history, /*cap=*/1));
}

}  // namespace catsxp_ads
