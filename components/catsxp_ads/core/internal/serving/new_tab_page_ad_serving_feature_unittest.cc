/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/new_tab_page_ad_serving_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsNewTabPageAdServingFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kNewTabPageAdServingFeature));
}

TEST(CatsxpAdsNewTabPageAdServingFeatureTest, NewTabPageAdServingVersion) {
  // Act & Assert
  EXPECT_EQ(2, kNewTabPageAdServingVersion.Get());
}

}  // namespace catsxp_ads
