/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/sampling/creative_ad_model_based_predictor_sampling_util.h"

#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/creative_ad_model_based_predictor_info.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsCreativeAdModelBasedPredictorSamplingUtilTest,
     CalculateNormalizingConstantForCreativeAdModelBasedPredictors) {
  // Arrange
  CreativeAdModelBasedPredictorList<CreativeNotificationAdInfo>
      creative_ad_predictors;

  CreativeAdModelBasedPredictorInfo<CreativeNotificationAdInfo>
      creative_ad_predictor_1;
  creative_ad_predictor_1.score = 0.5;
  creative_ad_predictors.push_back(creative_ad_predictor_1);

  CreativeAdModelBasedPredictorInfo<CreativeNotificationAdInfo>
      creative_ad_predictor_2;
  creative_ad_predictor_2.score = 1.0;
  creative_ad_predictors.push_back(creative_ad_predictor_2);

  // Act & Assert
  EXPECT_DOUBLE_EQ(
      1.5, CalculateNormalizingConstantForCreativeAdModelBasedPredictors(
               creative_ad_predictors));
}

}  // namespace catsxp_ads
