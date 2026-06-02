/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/input_variable/creative_ad_model_based_predictor_input_variable_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/test/creative_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/prediction/model_based/input_variable/segment/creative_ad_model_based_predictor_segment_input_variables_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/user_model_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/test/ad_event_builder_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsCreativeAdModelBasedPredictorInputVariableUtilTest
    : public test::TestBase {};

TEST_F(
    CatsxpAdsCreativeAdModelBasedPredictorInputVariableUtilTest,
    ComputeCreativeAdModelBasedPredictorMatchingChildIntentSegmentInputVariable) {
  // Arrange
  UserModelInfo user_model;
  user_model.intent.segments = {"parent-child", "xyzzy-thud"};

  // Act
  const CreativeAdModelBasedPredictorSegmentInputVariablesInfo
      intent_segment_input_variable =
          ComputeCreativeAdModelBasedPredictorIntentSegmentInputVariable(
              user_model, "parent-child", /*weights=*/{});

  // Assert
  EXPECT_TRUE(intent_segment_input_variable.child_matches.value);
  EXPECT_TRUE(intent_segment_input_variable.parent_matches.value);
}

TEST_F(
    CatsxpAdsCreativeAdModelBasedPredictorInputVariableUtilTest,
    ComputeCreativeAdModelBasedPredictorMatchingParentIntentSegmentInputVariable) {
  // Arrange
  UserModelInfo user_model;
  user_model.intent.segments = {"parent-child", "xyzzy-thud"};

  // Act
  const CreativeAdModelBasedPredictorSegmentInputVariablesInfo
      intent_segment_input_variable =
          ComputeCreativeAdModelBasedPredictorIntentSegmentInputVariable(
              user_model, "parent-foo", /*weights=*/{});

  // Assert
  EXPECT_FALSE(intent_segment_input_variable.child_matches.value);
  EXPECT_TRUE(intent_segment_input_variable.parent_matches.value);
}

TEST_F(
    CatsxpAdsCreativeAdModelBasedPredictorInputVariableUtilTest,
    ComputeCreativeAdModelBasedPredictorNonMatchingIntentSegmentInputVariable) {
  // Arrange
  UserModelInfo user_model;
  user_model.intent.segments = {"parent-child", "xyzzy-thud"};

  // Act
  const CreativeAdModelBasedPredictorSegmentInputVariablesInfo
      intent_segment_input_variable =
          ComputeCreativeAdModelBasedPredictorIntentSegmentInputVariable(
              user_model, "foo-bar", /*weights=*/{});

  // Assert
  EXPECT_FALSE(intent_segment_input_variable.child_matches.value);
  EXPECT_FALSE(intent_segment_input_variable.parent_matches.value);
}

TEST_F(
    CatsxpAdsCreativeAdModelBasedPredictorInputVariableUtilTest,
    ComputeCreativeAdModelBasedPredictorMatchingChildLatentInterestSegmentInputVariable) {
  // Arrange
  UserModelInfo user_model;
  user_model.latent_interest.segments = {"parent-child", "xyzzy-thud"};

  // Act
  const CreativeAdModelBasedPredictorSegmentInputVariablesInfo
      latent_interest_segment_input_variable =
          ComputeCreativeAdModelBasedPredictorLatentInterestSegmentInputVariable(
              user_model, "parent-child", /*weights=*/{});

  // Assert
  EXPECT_TRUE(latent_interest_segment_input_variable.child_matches.value);
  EXPECT_TRUE(latent_interest_segment_input_variable.parent_matches.value);
}

TEST_F(
    CatsxpAdsCreativeAdModelBasedPredictorInputVariableUtilTest,
    ComputeCreativeAdModelBasedPredictorMatchingParentLatentInterestSegmentInputVariable) {
  // Arrange
  UserModelInfo user_model;
  user_model.latent_interest.segments = {"parent-child", "xyzzy-thud"};

  // Act
  const CreativeAdModelBasedPredictorSegmentInputVariablesInfo
      latent_interest_segment_input_variable =
          ComputeCreativeAdModelBasedPredictorLatentInterestSegmentInputVariable(
              user_model, "parent-foo", /*weights=*/{});

  // Assert
  EXPECT_FALSE(latent_interest_segment_input_variable.child_matches.value);
  EXPECT_TRUE(latent_interest_segment_input_variable.parent_matches.value);
}

TEST_F(
    CatsxpAdsCreativeAdModelBasedPredictorInputVariableUtilTest,
    ComputeCreativeAdModelBasedPredictorNonMatchingLatentInterestSegmentInputVariable) {
  // Arrange
  UserModelInfo user_model;
  user_model.latent_interest.segments = {"parent-child", "xyzzy-thud"};

  // Act
  const CreativeAdModelBasedPredictorSegmentInputVariablesInfo
      latent_interest_segment_input_variable =
          ComputeCreativeAdModelBasedPredictorLatentInterestSegmentInputVariable(
              user_model, "foo-bar", /*weights=*/{});

  // Assert
  EXPECT_FALSE(latent_interest_segment_input_variable.child_matches.value);
  EXPECT_FALSE(latent_interest_segment_input_variable.parent_matches.value);
}

TEST_F(
    CatsxpAdsCreativeAdModelBasedPredictorInputVariableUtilTest,
    ComputeCreativeAdModelBasedPredictorMatchingChildInterestSegmentInputVariable) {
  // Arrange
  UserModelInfo user_model;
  user_model.interest.segments = {"parent-child", "xyzzy-thud"};

  // Act
  const CreativeAdModelBasedPredictorSegmentInputVariablesInfo
      interest_segment_input_variable =
          ComputeCreativeAdModelBasedPredictorInterestSegmentInputVariable(
              user_model, "parent-child", /*weights=*/{});

  // Assert
  EXPECT_TRUE(interest_segment_input_variable.child_matches.value);
  EXPECT_TRUE(interest_segment_input_variable.parent_matches.value);
}

TEST_F(
    CatsxpAdsCreativeAdModelBasedPredictorInputVariableUtilTest,
    ComputeCreativeAdModelBasedPredictorMatchingParentInterestSegmentInputVariable) {
  // Arrange
  UserModelInfo user_model;
  user_model.interest.segments = {"parent-child", "xyzzy-thud"};

  // Act
  const CreativeAdModelBasedPredictorSegmentInputVariablesInfo
      interest_segment_input_variable =
          ComputeCreativeAdModelBasedPredictorInterestSegmentInputVariable(
              user_model, "parent-foo", /*weights=*/{});

  // Assert
  EXPECT_FALSE(interest_segment_input_variable.child_matches.value);
  EXPECT_TRUE(interest_segment_input_variable.parent_matches.value);
}

TEST_F(
    CatsxpAdsCreativeAdModelBasedPredictorInputVariableUtilTest,
    ComputeCreativeAdModelBasedPredictorNonMatchingInterestSegmentInputVariable) {
  // Arrange
  UserModelInfo user_model;
  user_model.interest.segments = {"parent-child", "xyzzy-thud"};

  // Act
  const CreativeAdModelBasedPredictorSegmentInputVariablesInfo
      interest_segment_input_variable =
          ComputeCreativeAdModelBasedPredictorInterestSegmentInputVariable(
              user_model, "foo-bar", /*weights=*/{});

  // Assert
  EXPECT_FALSE(interest_segment_input_variable.child_matches.value);
  EXPECT_FALSE(interest_segment_input_variable.parent_matches.value);
}

TEST_F(CatsxpAdsCreativeAdModelBasedPredictorInputVariableUtilTest,
       ComputeCreativeAdModelBasedPredictorLastSeenAdInputVariable) {
  // Arrange
  const CreativeAdInfo creative_ad =
      test::BuildCreativeAd(/*use_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      test::BuildAdEvent(creative_ad, mojom::AdType::kNotificationAd,
                         mojom::ConfirmationType::kViewedImpression,
                         /*created_at=*/test::Now() - base::Hours(7),
                         /*use_random_uuids=*/true);
  ad_events.push_back(ad_event);

  const CreativeAdModelBasedPredictorLastSeenInputVariableInfo
      last_seen_ad_input_variable =
          ComputeCreativeAdModelBasedPredictorLastSeenAdInputVariable(
              creative_ad, ad_events, /*weight=*/0.0);

  // Act & Assert
  EXPECT_EQ(base::Hours(7), last_seen_ad_input_variable.value);
}

TEST_F(CatsxpAdsCreativeAdModelBasedPredictorInputVariableUtilTest,
       ComputeCreativeAdModelBasedPredictorLastSeenAdInputVariableIfNeverSeen) {
  // Arrange
  const CreativeAdInfo creative_ad =
      test::BuildCreativeAd(/*use_random_uuids=*/true);

  const CreativeAdModelBasedPredictorLastSeenInputVariableInfo
      last_seen_ad_input_variable =
          ComputeCreativeAdModelBasedPredictorLastSeenAdInputVariable(
              creative_ad, /*ad_events=*/{}, /*weight=*/0.0);

  // Act & Assert
  EXPECT_FALSE(last_seen_ad_input_variable.value);
}

}  // namespace catsxp_ads
