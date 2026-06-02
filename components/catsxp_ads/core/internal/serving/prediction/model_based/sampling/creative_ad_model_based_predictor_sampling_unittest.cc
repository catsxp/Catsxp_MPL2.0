/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/sampling/creative_ad_model_based_predictor_sampling.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/test/creative_notification_ad_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsCreativeAdModelBasedPredictorSamplingTest
    : public test::TestBase {};

TEST_F(CatsxpAdsCreativeAdModelBasedPredictorSamplingTest, SampleCreativeAd) {
  // Arrange
  CreativeAdModelBasedPredictorList<CreativeNotificationAdInfo>
      creative_ad_predictors;

  CreativeAdModelBasedPredictorInfo<CreativeNotificationAdInfo>
      creative_ad_predictor;
  creative_ad_predictor.creative_ad =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  creative_ad_predictor.score = 1.0;
  creative_ad_predictors.push_back(creative_ad_predictor);

  // Act & Assert
  EXPECT_EQ(creative_ad_predictor.creative_ad,
            MaybeSampleCreativeAd(creative_ad_predictors));
}

TEST_F(CatsxpAdsCreativeAdModelBasedPredictorSamplingTest,
       DeterministicallySampleCreativeAdWhenOneNonZeroScore) {
  // Arrange
  CreativeAdModelBasedPredictorList<CreativeNotificationAdInfo>
      creative_ad_predictors;

  CreativeAdModelBasedPredictorInfo<CreativeNotificationAdInfo>
      creative_ad_predictor_1;
  creative_ad_predictor_1.creative_ad =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  creative_ad_predictor_1.score = 0.0;
  creative_ad_predictors.push_back(creative_ad_predictor_1);

  CreativeAdModelBasedPredictorInfo<CreativeNotificationAdInfo>
      creative_ad_predictor_2;
  creative_ad_predictor_2.creative_ad =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  creative_ad_predictor_2.score = 1.0;
  creative_ad_predictors.push_back(creative_ad_predictor_2);

  CreativeAdModelBasedPredictorInfo<CreativeNotificationAdInfo>
      creative_ad_predictor_3;
  creative_ad_predictor_3.creative_ad =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  creative_ad_predictor_3.score = 0.0;
  creative_ad_predictors.push_back(creative_ad_predictor_3);

  // Act & Assert
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(creative_ad_predictor_2.creative_ad,
              MaybeSampleCreativeAd(creative_ad_predictors));
  }
}

TEST_F(CatsxpAdsCreativeAdModelBasedPredictorSamplingTest,
       ProbabilisticallySampleCreativeAd) {
  // Arrange
  CreativeAdModelBasedPredictorList<CreativeNotificationAdInfo>
      creative_ad_predictors;

  CreativeAdModelBasedPredictorInfo<CreativeNotificationAdInfo>
      creative_ad_predictor_1;
  creative_ad_predictor_1.creative_ad =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  creative_ad_predictor_1.score = 3.0;
  creative_ad_predictors.push_back(creative_ad_predictor_1);

  CreativeAdModelBasedPredictorInfo<CreativeNotificationAdInfo>
      creative_ad_predictor_2;
  creative_ad_predictor_2.creative_ad =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  creative_ad_predictor_2.score = 3.0;
  creative_ad_predictors.push_back(creative_ad_predictor_2);

  // Act & Assert
  size_t creative_ad_1_count = 0;
  size_t creative_ad_2_count = 0;

  for (size_t i = 0; i < 25; ++i) {
    // P(X>1) > 0.99999999 with X~Bin(n=25, p=0.5), i.e. less than 1 in 100M
    // tests are expected to fail.
    std::optional<CreativeNotificationAdInfo> creative_ad =
        MaybeSampleCreativeAd(creative_ad_predictors);
    ASSERT_TRUE(creative_ad);

    if (creative_ad->creative_instance_id ==
        creative_ad_predictor_1.creative_ad.creative_instance_id) {
      ++creative_ad_1_count;
    } else if (creative_ad->creative_instance_id ==
               creative_ad_predictor_2.creative_ad.creative_instance_id) {
      ++creative_ad_2_count;
    }
  }

  EXPECT_NE(0U, creative_ad_1_count);
  EXPECT_NE(0U, creative_ad_2_count);
}

TEST_F(CatsxpAdsCreativeAdModelBasedPredictorSamplingTest,
       DoNotSampleCreativeAd) {
  // Arrange
  CreativeAdModelBasedPredictorList<CreativeNotificationAdInfo>
      creative_ad_predictors;

  CreativeAdModelBasedPredictorInfo<CreativeNotificationAdInfo>
      creative_ad_predictor;
  creative_ad_predictor.creative_ad =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  creative_ad_predictor.score = 0.0;
  creative_ad_predictors.push_back(creative_ad_predictor);

  // Act & Assert
  EXPECT_FALSE(MaybeSampleCreativeAd(creative_ad_predictors));
}

}  // namespace catsxp_ads
