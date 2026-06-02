/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/creative_new_tab_page_ad_model_based_predictor_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(
      kCreativeNewTabPageAdModelBasedPredictorFeature));
}

TEST(CatsxpAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest,
     ChildIntentSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, kNewTabPageAdChildIntentSegmentPredictorWeight.Get());
}

TEST(CatsxpAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest,
     ParentIntentSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, kNewTabPageAdParentIntentSegmentPredictorWeight.Get());
}

TEST(CatsxpAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest,
     ChildLatentInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(
      0.0, kNewTabPageAdChildLatentInterestSegmentPredictorWeight.Get());
}

TEST(CatsxpAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest,
     ParentLatentInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(
      0.0, kNewTabPageAdParentLatentInterestSegmentPredictorWeight.Get());
}

TEST(CatsxpAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest,
     ChildInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, kNewTabPageAdChildInterestSegmentPredictorWeight.Get());
}

TEST(CatsxpAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest,
     ParentInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0,
                   kNewTabPageAdParentInterestSegmentPredictorWeight.Get());
}

TEST(CatsxpAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest,
     UntargetedSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0001, kNewTabPageAdUntargetedSegmentPredictorWeight.Get());
}

TEST(CatsxpAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest,
     LastSeenAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, kNewTabPageAdLastSeenPredictorWeight.Get());
}

}  // namespace catsxp_ads
