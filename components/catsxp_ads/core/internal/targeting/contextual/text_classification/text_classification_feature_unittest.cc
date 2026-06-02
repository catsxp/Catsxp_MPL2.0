/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/text_classification_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsTextClassificationFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kTextClassificationFeature));
}

TEST(CatsxpAdsTextClassificationFeatureTest, TextClassificationResourceVersion) {
  // Act & Assert
  EXPECT_EQ(1, kTextClassificationResourceVersion.Get());
}

TEST(CatsxpAdsTextClassificationFeatureTest,
     TextClassificationPageProbabilitiesHistorySize) {
  // Act & Assert
  EXPECT_EQ(15U, kTextClassificationPageProbabilitiesHistorySize.Get());
}

}  // namespace catsxp_ads
