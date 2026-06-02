/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsNewTabPageAdFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kNewTabPageAdFeature));
}

TEST(CatsxpAdsNewTabPageAdFeatureTest, MaximumNewTabPageAdsPerHour) {
  // Act & Assert
  EXPECT_EQ(4U, kMaximumNewTabPageAdsPerHour.Get());
}

TEST(CatsxpAdsNewTabPageAdFeatureTest, MaximumNewTabPageAdsPerDay) {
  // Act & Assert
  EXPECT_EQ(20U, kMaximumNewTabPageAdsPerDay.Get());
}

TEST(CatsxpAdsNewTabPageAdFeatureTest, NewTabPageAdMinimumWaitTime) {
  // Act & Assert
  EXPECT_EQ(base::Minutes(1), kNewTabPageAdMinimumWaitTime.Get());
}

}  // namespace catsxp_ads
