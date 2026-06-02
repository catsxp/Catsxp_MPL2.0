/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/segments/top_user_model_segments_util.h"

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/intent/intent_user_model_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/interest/interest_user_model_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/latent_interest/latent_interest_user_model_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/user_model_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

constexpr size_t kTopSegmentsMaxCount = 2;

UserModelInfo BuildUserModel() {
  return UserModelInfo{
      IntentUserModelInfo{SegmentList{"intent_1_parent-child",
                                      "intent_2_parent-child",
                                      "intent_3_parent-child"}},
      LatentInterestUserModelInfo{SegmentList{
          "latent_interest_1_parent-child", "latent_interest_2_parent-child",
          "latent_interest_3_parent-child"}},
      InterestUserModelInfo{SegmentList{"interest_1_parent-child",
                                        "interest_2_parent-child",
                                        "interest_3_parent-child"}}};
}

}  // namespace

class CatsxpAdsTopUserModelSegmentsUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsTopUserModelSegmentsUtilTest, GetTopChildSegments) {
  // Arrange
  const UserModelInfo user_model = BuildUserModel();

  // Act
  const SegmentList top_segments =
      GetTopSegments(user_model, kTopSegmentsMaxCount, /*parent_only=*/false);

  // Assert
  const SegmentList expected_top_segments = {
      "intent_1_parent-child",          "intent_2_parent-child",
      "latent_interest_1_parent-child", "latent_interest_2_parent-child",
      "interest_1_parent-child",        "interest_2_parent-child"};
  EXPECT_EQ(expected_top_segments, top_segments);
}

TEST_F(CatsxpAdsTopUserModelSegmentsUtilTest, GetTopChildSegmentsIfEmpty) {
  EXPECT_THAT(GetTopSegments(/*user_model=*/{}, kTopSegmentsMaxCount,
                             /*parent_only=*/false),
              ::testing::IsEmpty());
}

TEST_F(CatsxpAdsTopUserModelSegmentsUtilTest, GetTopParentSegmentsIfEmpty) {
  EXPECT_THAT(GetTopSegments(/*user_model=*/{}, kTopSegmentsMaxCount,
                             /*parent_only=*/true),
              ::testing::IsEmpty());
}

TEST_F(CatsxpAdsTopUserModelSegmentsUtilTest, GetTopParentSegments) {
  // Arrange
  const UserModelInfo user_model = BuildUserModel();

  // Act
  const SegmentList top_segments =
      GetTopSegments(user_model, kTopSegmentsMaxCount, /*parent_only=*/true);

  // Assert
  const SegmentList expected_top_segments = {
      "intent_1_parent",          "intent_2_parent",
      "latent_interest_1_parent", "latent_interest_2_parent",
      "interest_1_parent",        "interest_2_parent"};
  EXPECT_EQ(expected_top_segments, top_segments);
}

}  // namespace catsxp_ads
