/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/segments/top_user_model_segments.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/intent/intent_user_model_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/interest/interest_user_model_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/latent_interest/latent_interest_user_model_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/user_model_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

UserModelInfo BuildUserModel() {
  return UserModelInfo{
      IntentUserModelInfo{
          SegmentList{"intent_1_parent-child", "intent_2_parent-child"}},
      LatentInterestUserModelInfo{SegmentList{
          "latent_interest_1_parent-child", "latent_interest_2_parent-child"}},
      InterestUserModelInfo{
          SegmentList{"interest_1_parent-child", "interest_2_parent-child"}}};
}

}  // namespace

class CatsxpAdsTopUserModelSegmentsTest : public test::TestBase {};

TEST_F(CatsxpAdsTopUserModelSegmentsTest, GetTopChildSegments) {
  // Arrange
  const UserModelInfo user_model = BuildUserModel();

  // Act
  const SegmentList top_child_segments = GetTopChildSegments(user_model);

  // Assert
  const SegmentList expected_top_child_segments = {
      "intent_1_parent-child",          "intent_2_parent-child",
      "latent_interest_1_parent-child", "latent_interest_2_parent-child",
      "interest_1_parent-child",        "interest_2_parent-child"};
  EXPECT_EQ(expected_top_child_segments, top_child_segments);
}

TEST_F(CatsxpAdsTopUserModelSegmentsTest, GetTopParentSegments) {
  // Arrange
  const UserModelInfo user_model = BuildUserModel();

  // Act
  const SegmentList top_parent_segments = GetTopParentSegments(user_model);

  // Assert
  const SegmentList expected_top_parent_segments = {
      "intent_1_parent",          "intent_2_parent",
      "latent_interest_1_parent", "latent_interest_2_parent",
      "interest_1_parent",        "interest_2_parent"};
  EXPECT_EQ(expected_top_parent_segments, top_parent_segments);
}

TEST_F(CatsxpAdsTopUserModelSegmentsTest, GetTopChildIntentSegments) {
  // Arrange
  const UserModelInfo user_model = BuildUserModel();

  // Act
  const SegmentList top_child_intent_segments =
      GetTopChildIntentSegments(user_model);

  // Assert
  const SegmentList expected_top_child_intent_segments = {
      "intent_1_parent-child", "intent_2_parent-child"};
  EXPECT_EQ(expected_top_child_intent_segments, top_child_intent_segments);
}

TEST_F(CatsxpAdsTopUserModelSegmentsTest, GetTopParentIntentSegments) {
  // Arrange
  const UserModelInfo user_model = BuildUserModel();

  // Act
  const SegmentList top_parent_intent_segments =
      GetTopParentIntentSegments(user_model);

  // Assert
  const SegmentList expected_top_parent_intent_segments = {"intent_1_parent",
                                                           "intent_2_parent"};
  EXPECT_EQ(expected_top_parent_intent_segments, top_parent_intent_segments);
}

TEST_F(CatsxpAdsTopUserModelSegmentsTest, GetTopChildLatentInterestSegments) {
  // Arrange
  const UserModelInfo user_model = BuildUserModel();

  // Act
  const SegmentList top_child_latent_interest_segments =
      GetTopChildLatentInterestSegments(user_model);

  // Assert
  const SegmentList expected_top_child_latent_interest_segments = {
      "latent_interest_1_parent-child", "latent_interest_2_parent-child"};
  EXPECT_EQ(expected_top_child_latent_interest_segments,
            top_child_latent_interest_segments);
}

TEST_F(CatsxpAdsTopUserModelSegmentsTest, GetTopParentLatentInterestSegments) {
  // Arrange
  const UserModelInfo user_model = BuildUserModel();

  // Act
  const SegmentList top_parent_latent_interest_segments =
      GetTopParentLatentInterestSegments(user_model);

  // Assert
  const SegmentList expected_top_parent_latent_interest_segments = {
      "latent_interest_1_parent", "latent_interest_2_parent"};
  EXPECT_EQ(expected_top_parent_latent_interest_segments,
            top_parent_latent_interest_segments);
}

TEST_F(CatsxpAdsTopUserModelSegmentsTest, GetTopChildInterestSegments) {
  // Arrange
  const UserModelInfo user_model = BuildUserModel();

  // Act
  const SegmentList top_child_interest_segments =
      GetTopChildInterestSegments(user_model);

  // Assert
  const SegmentList expected_top_child_interest_segments = {
      "interest_1_parent-child", "interest_2_parent-child"};
  EXPECT_EQ(expected_top_child_interest_segments, top_child_interest_segments);
}

TEST_F(CatsxpAdsTopUserModelSegmentsTest, GetTopParentInterestSegments) {
  // Arrange
  const UserModelInfo user_model = BuildUserModel();

  // Act
  const SegmentList top_parent_interest_segments =
      GetTopParentInterestSegments(user_model);

  // Assert
  const SegmentList expected_top_parent_interest_segments = {
      "interest_1_parent", "interest_2_parent"};
  EXPECT_EQ(expected_top_parent_interest_segments,
            top_parent_interest_segments);
}

}  // namespace catsxp_ads
