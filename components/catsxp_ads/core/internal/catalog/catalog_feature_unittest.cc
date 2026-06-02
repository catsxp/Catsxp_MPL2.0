/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsCatalogFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kCatalogFeature));
}

TEST(CatsxpAdsCatalogFeatureTest, CatalogLifespan) {
  // Act & Assert
  EXPECT_EQ(base::Days(1), kCatalogLifespan.Get());
}

}  // namespace catsxp_ads
