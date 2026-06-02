/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/statement/statement_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsAccountFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kAccountStatementFeature));
}

TEST(CatsxpAdsAccountFeatureTest, NextPaymentDay) {
  // Act & Assert
  EXPECT_EQ(7, kNextPaymentDay.Get());
}

TEST(CatsxpAdsAccountFeatureTest, MinEstimatedEarningsMultiplier) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.8, kMinEstimatedEarningsMultiplier.Get());
}

}  // namespace catsxp_ads
