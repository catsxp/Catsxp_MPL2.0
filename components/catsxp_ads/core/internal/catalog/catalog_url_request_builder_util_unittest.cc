/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_url_request_builder_util.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsCatalogUrlRequestBuilderUtilTest, GetPath) {
  // Act & Assert
  EXPECT_EQ("/v9/catalog", BuildCatalogUrlPath());
}

}  // namespace catsxp_ads
