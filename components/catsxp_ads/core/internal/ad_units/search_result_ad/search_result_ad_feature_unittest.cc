/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsSearchResultAdFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kSearchResultAdFeature));
}

TEST(CatsxpAdsSearchResultAdFeatureTest, MaximumSearchResultAdsPerHour) {
  // Act & Assert
  EXPECT_EQ(0U, kMaximumSearchResultAdsPerHour.Get());
}

TEST(CatsxpAdsSearchResultAdFeatureTest, MaximumSearchResultAdsPerDay) {
  // Act & Assert
  EXPECT_EQ(0U, kMaximumSearchResultAdsPerDay.Get());
}

}  // namespace catsxp_ads
