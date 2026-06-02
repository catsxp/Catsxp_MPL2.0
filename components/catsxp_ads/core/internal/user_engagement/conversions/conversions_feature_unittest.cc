/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversions_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsConversionsFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kConversionsFeature));
}

TEST(CatsxpAdsConversionsFeatureTest, ConversionResourceVersion) {
  // Act & Assert
  EXPECT_EQ(1, kConversionResourceVersion.Get());
}

TEST(CatsxpAdsConversionsFeatureTest, HtmlMetaTagConversionIdPattern) {
  // Act & Assert
  EXPECT_EQ(R"~(<meta.*name="ad-conversion-id".*content="([-a-zA-Z0-9]*)".*>)~",
            kHtmlMetaTagConversionIdPattern.Get());
}

}  // namespace catsxp_ads
