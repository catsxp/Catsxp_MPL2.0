/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/creative_notification_ad_model_based_predictor_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsCreativeNotificationAdModelBasedPredictorFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(
      kCreativeNotificationAdModelBasedPredictorFeature));
}

TEST(CatsxpAdsCreativeNotificationAdModelBasedPredictorFeatureTest,
     ChildIntentSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(1.0, kNotificationAdChildIntentSegmentPredictorWeight.Get());
}

TEST(CatsxpAdsCreativeNotificationAdModelBasedPredictorFeatureTest,
     ParentIntentSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(1.0,
                   kNotificationAdParentIntentSegmentPredictorWeight.Get());
}

TEST(CatsxpAdsCreativeNotificationAdModelBasedPredictorFeatureTest,
     ChildLatentInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(
      1.0, kNotificationAdChildLatentInterestSegmentPredictorWeight.Get());
}

TEST(CatsxpAdsCreativeNotificationAdModelBasedPredictorFeatureTest,
     ParentLatentInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(
      1.0, kNotificationAdParentLatentInterestSegmentPredictorWeight.Get());
}

TEST(CatsxpAdsCreativeNotificationAdModelBasedPredictorFeatureTest,
     ChildInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(1.0,
                   kNotificationAdChildInterestSegmentPredictorWeight.Get());
}

TEST(CatsxpAdsCreativeNotificationAdModelBasedPredictorFeatureTest,
     ParentInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(1.0,
                   kNotificationAdParentInterestSegmentPredictorWeight.Get());
}

TEST(CatsxpAdsCreativeNotificationAdModelBasedPredictorFeatureTest,
     UntargetedSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0001,
                   kNotificationAdUntargetedSegmentPredictorWeight.Get());
}

TEST(CatsxpAdsCreativeNotificationAdModelBasedPredictorFeatureTest,
     LastSeenAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, kNotificationAdLastSeenPredictorWeight.Get());
}

}  // namespace catsxp_ads
