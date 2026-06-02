/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/weight/creative_new_tab_page_ad_model_based_predictor_weights_builder.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/weight/creative_ad_model_based_predictor_weights_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsCreativeNewTabPageAdModelBasedPredictorWeightsBuilderTest
    : public test::TestBase {};

TEST_F(CatsxpAdsCreativeNewTabPageAdModelBasedPredictorWeightsBuilderTest,
       BuildCreativeNewTabPageAdModelBasedPredictorWeights) {
  // Act
  const CreativeAdModelBasedPredictorWeightsInfo weights =
      BuildCreativeNewTabPageAdModelBasedPredictorWeights();

  // Assert
  CreativeAdModelBasedPredictorWeightsInfo expected_weights;
  expected_weights.intent_segment.child = 0.0;
  expected_weights.intent_segment.parent = 0.0;
  expected_weights.latent_interest_segment.child = 0.0;
  expected_weights.latent_interest_segment.parent = 0.0;
  expected_weights.interest_segment.child = 0.0;
  expected_weights.interest_segment.parent = 0.0;
  expected_weights.untargeted_segment = 0.0001;
  expected_weights.last_seen_ad = 0.0;
  EXPECT_EQ(expected_weights, weights);
}

}  // namespace catsxp_ads
